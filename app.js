'use strict';

const Homey = require('homey');
const dgram = require('dgram');
const { fetch } = require('undici');

function isValidIPAddress(ipaddress) {
  // Check if ipaddress is undefined or null
  if (ipaddress === undefined || ipaddress === null) {
    return false; // Not a valid IP address
  }

  // Regular expression for IPv4 validation
  const ipPattern = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;

  // Validate IP address pattern
  return ipPattern.test(ipaddress);
}

class iZoneApp extends Homey.App {

  async onInit() {
    this.log(`${this.id} running...`);

    // uncomment only for testing !!
    // this.homey.settings.unset('izone.ipaddress');
    this.enableRespDebug = false;

    this.ipaddress = this.homey.settings.get('izone.ipaddress');

    if (!isValidIPAddress(this.ipaddress)) {
      this.homey.app.sendMessageAndReturnAddress()
        .then(address => {
          console.log('Remote address:', address);
          this.homey.settings.set('izone.ipaddress', address);
          this.ipaddress = address;
        })
        .catch(error => {
          console.error('Error occurred:', error);
        });
    }


    this.state = {};
    this.state.ilight = {};
    this.state.ilight.lights = {};

    // getFirmwareList
    let resultFmw = await this.getFirmwareList();
    if (resultFmw.status === "ok") {
      this.state.firmware = resultFmw.Fmw;
    }
    this.startPolling();
  }

  async onUninit() {
    this.pausePolling();
  }

  isPaused = false; // This flag checks if the polling is paused

  async resetPolling() {
    this.pausePolling();
    setTimeout(() => {
      this.resumePolling();
    }, 500);
  }

  async startPolling() {
    setTimeout(() => {
      if (!this.isPaused) {
        this.polling().then(() => {
          this.startPolling(); // Recursively start polling again
        });
      }
    }, 200); // Wait for 200ms before the next poll
  }

  async pausePolling() {
    this.isPaused = true; // This pauses the polling
  }

  async resumePolling() {
    if (this.isPaused) {
      this.isPaused = false;
      this.startPolling(); // Resume polling
    }
  }

  async polling() {
    if (this.refreshLightList === undefined) {
      // starting or repeating, so do getiLightSystemInfo 
      this.refreshLightList = [];
      let result = await this.getiLightSystemInfo();

      if (result.status === "ok") {
        this.state.ilight.sysinfo = result.iLightSystem;
        for (let i = 0; i < result.iLightSystem.LiNext; i++) {
          this.refreshLightList.push(i);
        }
      }
      return;
    }

    // now pop a light num and do getLightInfo...
    const lightNum = this.refreshLightList.pop();
    if (lightNum != undefined) {
      const resultLight = await this.getLightInfo(lightNum);
      if (resultLight.status === "ok") {
        let lightIdx = "L" + resultLight.iLight.Index;
        this.state.ilight.lights[lightIdx] = resultLight.iLight;
        this.updateCapabilitiesDeviceId(lightIdx);
      }
      return;
    }
    // pop failed so reset refreshLightList
    this.refreshLightList = undefined;
  }

  async getiLightSystemInfo() {
    if (!isValidIPAddress(this.ipaddress)) return {};
    const uri = `http://${this.ipaddress}:80/iLightRequest`;
    if (this.enableRespDebug) this.log(`getiLightSystemInfo() ${uri}`);
    let respData = {};

    const mapBody = { "LiRequest": { "Type": 2, "No": 0, "No1": 0 } };

    try {
      respData.status = "failed";
      const response = await fetch(uri, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(mapBody)
      });
      const responseData = await response.json();

      respData = responseData;
      if (respData.hasOwnProperty("iLightSystem")) respData.status = "ok";
    } catch (e) {
      if (this.enableRespDebug) this.log(`getiLightSystemInfo() ERROR: ${e}`);
      respData.status = "failed: " + e;
    }
    return respData;
  }

  async getLightInfo(indexL) {
    if (!isValidIPAddress(this.ipaddress)) return {};
    const uri = `http://${this.ipaddress}:80/iLightRequest`;
    if (this.enableRespDebug) this.log(`getLightInfo() ${uri} ${indexL}`);
    let respData = {};

    const mapBody = { "LiRequest": { "Type": 1, "No": indexL, "No1": 0 } };

    try {
      respData.status = "failed";
      const response = await fetch(uri, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(mapBody)
      });
      const responseData = await response.json();

      respData = responseData;
      if (respData.hasOwnProperty("iLight")) respData.status = "ok";
    } catch (e) {
      if (this.enableRespDebug) this.log(`getLightInfo() ERROR: ${e}`);
      respData.status = "failed: " + e;
    }
    return respData;
  }

  async updateCapabilitiesDeviceId(id) {
    // update the drivers and devices
    const drivers = this.homey.drivers.getDrivers();
    for (const driver in drivers) {
      const devices = this.homey.drivers.getDriver(driver).getDevices();
      for (const device of devices) {
        if (device.getData().id === id && device.updateCapabilities) {
          device.updateCapabilities();
          break;
        }
      }
    }
  }

  async getFirmwareList() {
    if (!isValidIPAddress(this.ipaddress)) return {};
    const uri = `http://${this.ipaddress}:80/iZoneRequestV2`;
    if (this.enableRespDebug) this.log(`getFirmwareList() ${uri}`);
    let respData = {};

    const mapBody = { "iZoneV2Request": { "Type": 6, "No": 0, "No1": 0 } };

    try {
      respData.status = "failed";
      const response = await fetch(uri, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(mapBody)
      });
      const responseData = await response.json();

      respData = responseData;
      if (respData.hasOwnProperty("Fmw")) respData.status = "ok";
    } catch (e) {
      if (this.enableRespDebug) this.log(`getFirmwareList() ERROR: ${e}`);
      respData.status = "failed: " + e;
    }
    return respData;
  }

  async sendSimpleiLightCmd(cmd, value) {
    if (!isValidIPAddress(this.ipaddress)) return {};
    return this.sendSimpleUriCmdWithBody(
      `http://${this.ipaddress}:80/iLightCommand`,
      JSON.stringify({ [cmd]: value }));
  }

  async sendSimpleUriCmdWithBody(uri, cmdbody) {
    const params = {
      uri: uri,
      body: cmdbody,
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      }
    };

    if (this.enableRespDebug) this.log(`sendSimpleUriCmdWithBody() params: ${JSON.stringify(params)}`);

    try {
      const response = await fetch(params.uri, {
        method: params.method,
        headers: params.headers,
        body: params.body
      });

      const respData = await response.text();

      return { status: respData };
    } catch (e) {
      if (this.enableRespDebug) this.log(`sendSimpleUriCmdWithBody() ERROR: ${e}`);
      return { status: `failed: ${e}` };
    }
  }

  async sendMessageAndReturnAddress() {
    return new Promise((resolve, reject) => {
      const socket = dgram.createSocket('udp4');
      let remoteAddress;

      // Set up event listeners and binding only once
      socket.once('message', (message, remote) => {
        if (this.enableRespDebug) this.log(`CLIENT RECEIVED: ${remote.address} : ${remote.port} - ${message}`);
        remoteAddress = remote.address;
        resolve(remoteAddress);
      });

      socket.on('error', (err) => {
        reject(err);
      });

      socket.bind(() => {
        socket.setBroadcast(true);
        socket.send('IASD', 0, 4, 12107, '255.255.255.255', (err) => {
          if (err) {
            reject(err);
          }
        });
      });

      // Close the socket after 1 second if no response is received
      setTimeout(() => {
        if (!remoteAddress) {
          socket.close();
          reject(new Error('No response received'));
        }
      }, 1000);
    });
  }
}

module.exports = iZoneApp;
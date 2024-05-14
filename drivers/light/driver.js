'use strict';

const { Driver } = require('homey');

class iZoneLightDriver extends Driver {

  /**
   * onInit is called when the driver is initialized.
   */
  async onInit() {
    this.log('iZoneACDriver has been initialized');
  }

  /**
   * onPairListDevices is called when a user is adding a device
   * and the 'list_devices' view is called.
   * This should return an array with the data of devices that are available for pairing.
   */
  async onPairListDevices() {
    var devices = [];
    for (const keyid in this.homey.app.state.ilight.lights) {
      const light = this.homey.app.state.ilight.lights[keyid];
      const device = { name: light.Name, data: { id: keyid } }; 
      devices.push(device);
    }

    return devices;
  }

}

module.exports = iZoneLightDriver;

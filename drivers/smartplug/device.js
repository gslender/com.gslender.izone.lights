'use strict';

const { Device } = require('homey');
const iZoneTypes = require('../../izonetypes');
const colorconvert = require('color-convert');
var tempconvert = require('color-temp');

class iZoneSmartPlugDevice extends Device {

  /**
   * onInit is called when the device is initialized.
   */
  async onInit() {
    this.log('iZoneSmartPlugDevice has been initialized');

    this.registerCapabilityListener("onoff", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;
      await this.homey.app.sendSimpleiLightCmd("LiOn", { No: light.Index, On: value ? 1 : 0 });
      this.homey.app.pausePolling(500);
    });

  }

  getThisLight() {
    if (this.homey.app.state?.ilight?.lights?.[this.getData().id]) return this.homey.app.state.ilight.lights[this.getData().id]
    return undefined;
  }

  async updateCapabilities() {
    const light = this.getThisLight();
    if (light == undefined) return;
    this.setCapabilityValue('onoff', light.On === 1);
  }
}

module.exports = iZoneSmartPlugDevice;

'use strict';

const { Device } = require('homey');
const colorconvert = require('color-convert');
// var tempconvert = require('color-temp');

const POLLING_DELAY = 1000;

class iZoneLightDevice extends Device {

  /**
   * onInit is called when the device is initialized.
   */
  async onInit() {
    this.log('iZoneLightDevice has been initialized');
    let self = this;
    this.newColor = { hue: 360, sat: 100, lev: 50 };

    this.registerCapabilityListener("onoff", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;
      await this.homey.app.sendSimpleiLightCmd("LiOn", { No: light.Index, On: value ? 1 : 0 });
      this.homey.app.pausePolling(POLLING_DELAY);
    });

    this.registerCapabilityListener("dim", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;
      await this.homey.app.sendSimpleiLightCmd("LiBright", { No: light.Index, Bright: value * 100 });
      if (!this.getCapabilityValue('onoff')) await this.homey.app.sendSimpleiLightCmd("LiOn", { No: light.Index, On: 1 });
      this.homey.app.pausePolling(POLLING_DELAY);
    });

    this.registerCapabilityListener("light_mode", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;
      if (value === 'color') {
        this.homey.clearTimeout(this.colorChangeTimerId);
        // this.newColor.lev = this.getCapabilityValue('dim') * 100;
        this.newColor.sat = this.getCapabilityValue('light_saturation') * 100;
        this.newColor.hue = this.getCapabilityValue('light_hue') * 360;
        this.colorChangeTimerId = this.homey.setTimeout(() => {
          this.updateColor(light);
        }, 500);
      } else {
        const temp = this.getCapabilityValue('light_temperature');
        await this.homey.app.sendSimpleiLightCmd("LiTemp", { No: light.Index, Temp: temp });
      }
      this.homey.app.pausePolling(POLLING_DELAY);
    });

    this.registerCapabilityListener("light_hue", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;

      this.homey.clearTimeout(this.colorChangeTimerId);
      // this.newColor.lev = this.getCapabilityValue('dim') * 100;
      this.newColor.sat = this.getCapabilityValue('light_saturation') * 100;
      this.newColor.hue = value * 360;
      this.colorChangeTimerId = this.homey.setTimeout(() => {
        this.updateColor(light);
      }, 500);
    });

    this.registerCapabilityListener("light_saturation", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;

      this.homey.clearTimeout(this.colorChangeTimerId);
      // this.newColor.lev = this.getCapabilityValue('dim') * 100;
      this.newColor.sat = value * 100;
      this.newColor.hue = this.getCapabilityValue('light_hue') * 360;
      this.colorChangeTimerId = this.homey.setTimeout(() => {
        this.updateColor(light);
      }, 500);
    });

    this.registerCapabilityListener("light_temperature", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;
      await this.homey.app.sendSimpleiLightCmd("LiTemp", { No: light.Index, Temp: value * 100 });
      this.homey.app.pausePolling(POLLING_DELAY);
    });

  }

  async updateColor(light) {
    const rgb = colorconvert.hsl.rgb([this.newColor.hue, this.newColor.sat, this.newColor.lev]);
    this.log(`updateColor RGB=${[rgb[0], rgb[1], rgb[2]]}`);
    await this.homey.app.sendSimpleiLightCmd("LiRgb", { No: light.Index, R: rgb[0], G: rgb[1], B: rgb[2] });
    this.homey.app.pausePolling(POLLING_DELAY);
  }

  getThisLight() {
    if (this.homey.app.state?.ilight?.lights?.[this.getData().id]) return this.homey.app.state.ilight.lights[this.getData().id]
    return undefined;
  }

  async updateCapabilities() {
    const light = this.getThisLight();
    if (light == undefined) return;
    // this.log(`light=${JSON.stringify(light)}`);
    this.setCapabilityValue('onoff', light.On === 1);
    this.setCapabilityValue('dim', light.Brig / 100.0);
    if (light.Rgb === 1) {
      this.setCapabilityValue('light_mode', 'color');
      const hsl = colorconvert.rgb.hsl([light.R, light.G, light.B]);
      this.setCapabilityValue('light_hue', hsl[0] / 360);
      this.setCapabilityValue('light_saturation', hsl[1] / 100);
    } else {
      this.setCapabilityValue('light_mode', 'temperature');
      this.setCapabilityValue('light_temperature', light.Temp / 100.0);
    }
  }

}

module.exports = iZoneLightDevice;

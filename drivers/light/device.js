'use strict';

const { Device } = require('homey');
const iZoneTypes = require('../../izonetypes');
const colorconvert = require('color-convert');
var tempconvert = require('color-temp');

class iZoneLightDevice extends Device {

  /**
   * onInit is called when the device is initialized.
   */
  async onInit() {
    this.log('iZoneLightDevice has been initialized');

    this.registerCapabilityListener("onoff", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;
      this.homey.app.sendSimpleiLightCmd("LiOn", { No: light.Index, On: value ? 1 : 0 });
      this.homey.app.state = {};
      setTimeout(() => { this.homey.app.refresh(); }, 500);
    });

    this.registerCapabilityListener("dim", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;
      this.homey.app.sendSimpleiLightCmd("LiBright", { No: light.Index, Bright: value });
      this.homey.app.state = {};
      setTimeout(() => { this.homey.app.refresh(); }, 500);
    });

    this.registerCapabilityListener("light_mode", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;
      if (value === 'color') {
        const lev = this.getCapabilityValue('dim');
        const hue = this.getCapabilityValue('light_hue');
        const sat = this.getCapabilityValue('light_saturation');
        const rgb = colorconvert.hsl.rgb([hue, sat, lev]);
        this.homey.app.sendSimpleiLightCmd("LiRgb", { No: light.Index, R: rgb[0], G: rgb[1], B: rgb[2] });
      } else {
        const temp = this.getCapabilityValue('light_temperature');
        this.homey.app.sendSimpleiLightCmd("LiTemp", { No: light.Index, Temp: temp });
      }
      this.homey.app.state = {};
      setTimeout(() => { this.homey.app.refresh(); }, 500);
    });

    this.registerCapabilityListener("light_hue", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;
      const lev = this.getCapabilityValue('dim');
      const sat = this.getCapabilityValue('light_saturation');
      const rgb = colorconvert.hsl.rgb([value, sat, lev]);
      this.homey.app.sendSimpleiLightCmd("LiRgb", { No: light.Index, R: rgb[0], G: rgb[1], B: rgb[2] });
      this.homey.app.state = {};
      setTimeout(() => { this.homey.app.refresh(); }, 500);
    });

    this.registerCapabilityListener("light_saturation", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;
      const lev = this.getCapabilityValue('dim');
      const hue = this.getCapabilityValue('light_hue');
      const rgb = colorconvert.hsl.rgb([hue, value, lev]);
      this.homey.app.sendSimpleiLightCmd("LiRgb", { No: light.Index, R: rgb[0], G: rgb[1], B: rgb[2] });
      this.homey.app.state = {};
      setTimeout(() => { this.homey.app.refresh(); }, 500);
    });

    this.registerCapabilityListener("light_temperature", async (value) => {
      const light = this.getThisLight();
      if (light == undefined) return;
      this.homey.app.sendSimpleiLightCmd("LiTemp", { No: light.Index, Temp: value });
      this.homey.app.state = {};
      setTimeout(() => { this.homey.app.refresh(); }, 500);
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
    if (light.Type === 'CL5') {
      this.setCapabilityValue('dim', light.Brig);
      if (light.Rgb === 1) {
        this.setCapabilityValue('light_mode', 'color');
        const hsl = colorconvert.rgb.hsl([light.R, light.G, light.B]);
        this.setCapabilityValue('light_hue', hsl[0] / 360);
        this.setCapabilityValue('light_saturation', hsl[1] / 100);
        const tk = tempconvert.rgb2temp([light.R, light.G, light.B]);
        this.setCapabilityValue('light_temperature', tk / 6504);
      } else {
        this.setCapabilityValue('light_mode', 'temperature');
        this.setCapabilityValue('light_temperature', light.Temp / 6504);
        const rgb = tempconvert.temp2rgb(light.Temp);
        const hsl = colorconvert.rgb.hsl(rgb);
        this.setCapabilityValue('light_hue', hsl[0] / 360);
        this.setCapabilityValue('light_saturation', hsl[1] / 100);
      }
    }
  }
}

module.exports = iZoneLightDevice;

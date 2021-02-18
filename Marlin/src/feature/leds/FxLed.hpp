#pragma once

#include "leds.h"
#include "neopixel.h"
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

class LedFx
{

private:

uint32_t convert(LEDColor color){

  float ratio=float(color.i)/255.f;

  uint32_t r=uint8_t(float(color.r)*ratio);
  uint32_t g=uint8_t(float(color.g)*ratio);
  uint32_t b=uint8_t(float(color.b)*ratio);
  uint32_t w=uint8_t(float(color.w)*ratio);

  return (w<<24)|(r<<16)|(g<<8)|(b);
}


public:
  LedFx()
  {
  }

  enum class Pattern
  {
    Unitialized,
    Blink,
    FadeIn,
    FadeOut,
    BlinkID,
    FadeInBloc,
  };

public:
  void begin(Pattern pattern, uint32_t periodMs, LEDColor color, uint16_t id=0)
  {
    _periodMs = periodMs;
    _pattern = pattern;
    _color = color;
    _id = id;

    _lastMs = millis();

    if (pattern == Pattern::FadeOut)
      leds.set_color(color);
    else
      leds.set_color(0, 0, 0, 0);
  }

  void stop()
  {
    if (_pattern == Pattern::Blink)
    {
      leds.set_color(0, 0, 0, 0);
    }
  }

  void update()
  {
    if (_pattern == Pattern::Blink)
    {
      if (millis() - _lastMs > _periodMs)
      {
        _lastMs = millis();
        _color.i = _color.i ? 0 : 255;
        leds.set_color(_color);
      }
    }
    else if (_pattern == Pattern::FadeIn)
    {
      const auto dimmer = map(millis(), _lastMs, _lastMs + _periodMs, 0, 255);
      _color.i = dimmer;
      leds.set_color(_color);
    }
    else if (_pattern == Pattern::FadeOut)
    {
      const auto dimmer = map(millis(), _lastMs, _lastMs + _periodMs, 0, 255);
      _color.i = 255-dimmer;
      leds.set_color(_color);
    }
    else if (_pattern == Pattern::BlinkID)
    {
      if (millis() - _lastMs > _periodMs)
      {
        _lastMs = millis();
        _color.i = _color.i ? 0 : 255;
        neo.set_pixel_color(_id, convert(_color));
        neo.show();
      }
    }
    else if (_pattern == Pattern::FadeInBloc)
    {
      const auto dimmer = map(millis(), _lastMs, _lastMs + _periodMs, 0, 255);
      _color.i = dimmer;
      for(int i = 12; i < 39; ++i)
      neo.set_pixel_color(i, convert(_color));
      neo.show();
    }
  }

  Pattern _pattern = Pattern::Unitialized;
  uint32_t _periodMs = 0;
  uint32_t _lastMs = 0;
  LEDColor _color;
  uint16_t _id;
};

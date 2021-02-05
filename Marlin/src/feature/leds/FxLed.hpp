#pragma once

#include "leds.h"

class LedFx
{
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
  };

public:
  void begin(Pattern pattern, uint32_t periodMs, LEDColor color)
  {
    _periodMs = periodMs;
    _pattern = pattern;
    _color = color;

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
  }

  Pattern _pattern = Pattern::Unitialized;
  uint32_t _periodMs = 0;
  uint32_t _lastMs = 0;
  LEDColor _color;
};

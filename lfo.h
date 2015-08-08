// Copyright 2013 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// LFO.

#ifndef BATUMI_MODULATIONS_LFO_H_
#define BATUMI_MODULATIONS_LFO_H_

#include "stmlib/stmlib.h"

namespace batumi {

const int16_t kOctave = 12 * 128;
const int16_t kPitch1Hz = -32 * 128; /* TODO: ??? */
const int16_t kPitch10Hz = 4 * 128;
const int16_t kPitch100Hz = 44 * 128;

enum LfoShape {
  SHAPE_TRAPEZOID,
  SHAPE_RAMP,
  SHAPE_SAW,
  SHAPE_TRIANGLE,
};

class Lfo {
 public:
   
  Lfo() { }
  ~Lfo() { }
  
  void Init();
  void Step();

  inline void set_pitch(int16_t pitch) {
    phase_increment_ = ComputePhaseIncrement(pitch);
  };

  inline void set_phase(uint16_t phase) {
    initial_phase_ = phase << 16;
  }

  inline void set_divider(uint16_t divider) {
    divider_ = divider;
    // roughly take into account clock division for wave choice:
    divided_pitch_ = pitch_;
    for (uint16_t div = divider_; div > 1; div >>= 1, divided_pitch_ -= kOctave);
  }

  inline void set_level(uint16_t level) {
    level_ = level;
  }

  inline void Reset() {
    phase_ = 0;
  }

  int16_t ComputeSampleShape(LfoShape s);
  int16_t ComputeSampleSine();
  int16_t ComputeSampleTriangle();
  int16_t ComputeSampleTrapezoid();
  int16_t ComputeSampleRamp();
  int16_t ComputeSampleSaw();

 private:

  uint32_t ComputePhaseIncrement(int16_t pitch);
  int16_t pitch_;
  int16_t divided_pitch_;
  uint32_t phase_, divided_phase_;
  uint16_t divider_, divider_count_;
  uint16_t level_;
  uint32_t initial_phase_;
  uint32_t phase_increment_;

  DISALLOW_COPY_AND_ASSIGN(Lfo);
};

}  // namespace batumi

#endif  // BATUMI_MODULATIONS_LFO_H_

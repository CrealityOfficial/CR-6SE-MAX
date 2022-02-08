/**
 * Marlin 3D Printer Firmware
<<<<<<< HEAD
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
=======
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
>>>>>>> mcu_ctrl
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
<<<<<<< HEAD
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
=======
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
>>>>>>> mcu_ctrl
 *
 */
#pragma once

/**
 * Incremental Least Squares Best Fit  By Roxy and Ed Williams
 *
 * This algorithm is high speed and has a very small code footprint.
 * Its results are identical to both the Iterative Least-Squares published
 * earlier by Roxy and the QR_SOLVE solution. If used in place of QR_SOLVE
 * it saves roughly 10K of program memory.   And even better...  the data
 * fed into the algorithm does not need to all be present at the same time.
 * A point can be probed and its values fed into the algorithm and then discarded.
<<<<<<< HEAD
 *
=======
>>>>>>> mcu_ctrl
 */

#include "../inc/MarlinConfig.h"
#include <math.h>

struct linear_fit_data {
  float xbar, ybar, zbar,
<<<<<<< HEAD
        x2bar, y2bar, z2bar,
=======
        x2bar, y2bar,
>>>>>>> mcu_ctrl
        xybar, xzbar, yzbar,
        max_absx, max_absy,
        A, B, D, N;
};

inline void incremental_LSF_reset(struct linear_fit_data *lsf) {
  memset(lsf, 0, sizeof(linear_fit_data));
}

<<<<<<< HEAD
inline void incremental_WLSF(struct linear_fit_data *lsf, const float &x, const float &y, const float &z, const float &w) {
=======
inline void incremental_WLSF(struct linear_fit_data *lsf, const_float_t x, const_float_t y, const_float_t z, const_float_t w) {
>>>>>>> mcu_ctrl
  // weight each accumulator by factor w, including the "number" of samples
  // (analogous to calling inc_LSF twice with same values to weight it by 2X)
  const float wx = w * x, wy = w * y, wz = w * z;
  lsf->xbar  += wx;
  lsf->ybar  += wy;
  lsf->zbar  += wz;
  lsf->x2bar += wx * x;
  lsf->y2bar += wy * y;
<<<<<<< HEAD
  lsf->z2bar += wz * z;
=======
>>>>>>> mcu_ctrl
  lsf->xybar += wx * y;
  lsf->xzbar += wx * z;
  lsf->yzbar += wy * z;
  lsf->N     += w;
  lsf->max_absx = _MAX(ABS(wx), lsf->max_absx);
  lsf->max_absy = _MAX(ABS(wy), lsf->max_absy);
}
<<<<<<< HEAD
inline void incremental_WLSF(struct linear_fit_data *lsf, const xy_pos_t &pos, const float &z, const float &w) {
  incremental_WLSF(lsf, pos.x, pos.y, z, w);
}

inline void incremental_LSF(struct linear_fit_data *lsf, const float &x, const float &y, const float &z) {
=======
inline void incremental_WLSF(struct linear_fit_data *lsf, const xy_pos_t &pos, const_float_t z, const_float_t w) {
  incremental_WLSF(lsf, pos.x, pos.y, z, w);
}

inline void incremental_LSF(struct linear_fit_data *lsf, const_float_t x, const_float_t y, const_float_t z) {
>>>>>>> mcu_ctrl
  lsf->xbar += x;
  lsf->ybar += y;
  lsf->zbar += z;
  lsf->x2bar += sq(x);
  lsf->y2bar += sq(y);
<<<<<<< HEAD
  lsf->z2bar += sq(z);
=======
>>>>>>> mcu_ctrl
  lsf->xybar += x * y;
  lsf->xzbar += x * z;
  lsf->yzbar += y * z;
  lsf->max_absx = _MAX(ABS(x), lsf->max_absx);
  lsf->max_absy = _MAX(ABS(y), lsf->max_absy);
  lsf->N += 1.0;
}
<<<<<<< HEAD
inline void incremental_LSF(struct linear_fit_data *lsf, const xy_pos_t &pos, const float &z) {
=======
inline void incremental_LSF(struct linear_fit_data *lsf, const xy_pos_t &pos, const_float_t z) {
>>>>>>> mcu_ctrl
  incremental_LSF(lsf, pos.x, pos.y, z);
}

int finish_incremental_LSF(struct linear_fit_data *);

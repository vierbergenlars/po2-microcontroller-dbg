/*
 * timers.h
 *
 * Copyright (C) 2013 - Lars Vierbergen
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef HAVE_TIMERS_H
#define HAVE_TIMERS_H
void Delay1TCY();
void Delay10TCYx(unsigned char unit);
void Delay100TCYx(unsigned char unit);
void Delay1KTCYx(unsigned char unit);
void Delay10KTCYx(unsigned char unit);
#endif
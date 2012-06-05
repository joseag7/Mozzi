/*
 * AudioDelay.h
 *
 * Copyright 2012 unbackwards@gmail.com.
 *
 * This file is part of Cuttlefish.
 *
 * Cuttlefish is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cuttlefish is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cuttlefish.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef AUDIODELAY_H_
#define AUDIODELAY_H_


/** An audio delay line for comb filter, flange, chorus and short echo effects.
NUM_BUFFER_SAMPLES is the length of the delay buffer in samples, and should
be a power of two. The largest delay you'll fit in an atmega328 will be 512
cells, which at 16384 Hz sample rate is 31 milliseconds. More of a flanger or a
doubler than an echo. This version doesn't have feedback, for that use
AudioDelayFeedback instead. */

template <unsigned int NUM_BUFFER_SAMPLES>
class AudioDelay
{

private:

	char delay_array[NUM_BUFFER_SAMPLES];
	unsigned int write_pos;

public:

	/** Constructor. The length of the delay in samples is set in the
	template parameter, for example:
	AudioDelay <128> myAudioDelay();
	*/

	AudioDelay(): write_pos(0)
	{}


	/** Input a value to the delay and retrieve the signal in the delay line at the position delay_cells.
	*/
	inline
	char next(char in_value, unsigned int delay_cells)
	{
		++write_pos &= (NUM_BUFFER_SAMPLES - 1);
		unsigned int read_pos = (write_pos - delay_cells) & (NUM_BUFFER_SAMPLES - 1);

		// why does delay jump if I read it before writing?
		delay_array[write_pos] = in_value;			// write to buffer
		char delay_sig = delay_array[read_pos] ;	// read the delay buffer

		return (char)(((int) in_value + delay_sig)>>1);
	}

};

#endif        //  #ifndef AUDIODELAY_H_

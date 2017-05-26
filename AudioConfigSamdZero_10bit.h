#ifndef AUDIOCONFIGSAMDZERO_10BIT_H
#define AUDIOCONFIGSAMDZERO_10BIT_H


/** @ingroup core
*/
/* Used internally to put the 0-biased generated audio into the centre of the output range (10 bits on SAMD0) */
#define AUDIO_BIAS ((uint16_t) 512)

#define AUDIO_CHANNEL_1_PIN A0

#endif        //  #ifndef AUDIOCONFIGSAMDZERO_10BIT_H


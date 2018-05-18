#ifndef _DAYDREAM_H_
#define _DAYDREAM_H_

#include "mbed.h"

#define Do 261.626
#define Re 293.665
#define Mi 329.628
#define Fa 349.228
#define So 391.995
#define Ra 440.000
#define Si 493.883
#define Ky 1
#define No 2
#define mSi 493.883
#define mMi 329.628
#define mSo 391.995

float mm[] = {So*2, Ra*4, Si*4, Do*2, Ky, Do*2, Ky, Do*2, Do*2, Ky, Si*4, Si*4, Si*4, Ra*4, Ra*4, So*2, Ra*4, So*2, Fa*2, // kokoro pyon pyon machi kangaeru furishite
            Mi*4, Ky, Si*4, Ky, Mi*4, Ky, Si*4, No, Si*4, Do*2, Si*4, Ra*4, So*2, So*2, Ky,                                             // mouchotto chikazuichae
            Ra*4, Ra*4, Ra*4, Ra*4, Ra*4, Ra*4, Ky, So*2, No, So*2, So*2, Si*4, Do*4, Ky,                                               // kantanniha oshienai
            Fa*2, So*2, Ra*4, So*2, Mi*4, Ra*4, So*2, Mi*4, Do*2, Si*4, No, Si*4, Ky, Si*4, Si*4, Si*4, Do*2, Si*4, No,                 // konnani sukinakotoha naishonano
            Mi*2, Re*2, Mi*2, Si*4, Mi*2, Re*2, Mi*2, Si*4, Mi*2, Re*2, Mi*2, Fa*2, Fa*2, Mi*2, Ky,                                     // fuwa fuwa dokidoki naisho desuyo
            Mi*2, No, Mi*2, Re*2, Mi*2, Si*2, Mi*2, Re*2, Mi*2, So*2,                                                                   // hajime ga kanjin
            Ra*4, No, So*2, Fa*2, Fa*2, Mi*2, Ky, Mi*2, No, Mi*2, Re*2, Mi*2, Si*4, Mi*2, Re*2, Mi*2, Si*4,                             // tsunda tsunda fuwa fuwa doki doki
            Mi*2, Re*2, Mi*2, Fa*2, Fa*2, Mi*2, Ky, Mi*2, No, Mi*2, Re*2, Mi*2, Si*4, Ra*4, So*2, Fa*2, Mi*2,                           // naisho datte itazura egaode
            Re*2, Ky, Ky, Re*2, Ky,                                                                                                     // pyon pyon
            Do*2, Do*2, Mi*2, So*2, Ra*4, So*2, Mi*2, Do*2, Mi*2, Ky, So*2, No, So*2, Ra*4, So*2, Mi*2, Si*4, Ra*4, So*2, Ra*4, So*2,   // tobira aketa totan mishiranu sekai heto
            Ky, Ky, Ky, Ky, Ky, So*2, Ky, So*2, Ky, Ra*4, So*2,                                                                         // arienai
            Do*2, Do*2, Mi*2, So*2, Ra*4, So*2, Mi*2, Do*2, Mi*2, Ky,                                                                   // sorega arierukamo
            So*2, No, So*2, Ra*4, So*2, Mi*2, Si*4, Ra*4, So*2, Ra*2,                                                                   // miruku iro no ijigenn
            Mi*2, Re*2, Mi*2, Si*4, Mi*2, Re*2, Mi*2, So*2, So*2, So*2, So*2, Ra*4, So*2, Ky, Ky,                                       // ko-hi- kappu nozoitara
            Do*2, Re*2, Mi*2, Fa*2, Re*2, Mi*2, Fa*2, So*2, Mi*2, Fa*2, So*2, Ra*2, So*2, Fa*2, Mi*2, Ky,                               // watashi ga watashi wo mitsumete mashita
            Si*4, Mi*2, Ky, Si*4, Mi*2, Ky, Si*4, No, Si*4, Si*4, Ra*4, So*2, Mi*2, Ky,                                                 // nande nande futari iru
            Si*4, mMi*2, Do*4, Si*4, Si*4, Ra*4, So*2, Fa*2, Ky,                                                                        // usho komarimasune
            Ra*4, Ra*4, Ra*4, So*2, Fa*2, Mi*2, Ky,                                                                                     // onnaji shumi
            So*2, Fa*2, Mi*2,                                                                                                           // dare wo
            mSi*4, mSi*4, mSi*4, mSi*4, Mi*2, Si*4, Si*4, Mi*2, Si*2, Ky,                                                               // mitsukeruno kimi desho
            mMi*2, mMi*2, mMi*2, Mi*2, Mi*2, Do*2, Do*4,                                                                                // kimi dake miteru yo
            Do*2, No, Do*2, Si*2, Do*2, Ra*2, Ra*2, Ra*2, Ky, Mi*2, No, Mi*2, Re*2, Mi*2, Do*2, Do*2, Do*2, Ky,                         // koreha yume kappu no yume
            So*2, No, So*2, Fa*2, So*2, Mi*2, Mi*2, Mi*2, Ky, Si*4, No, Si*4, Si*4, Si*4, Si*4, Ky,                                     // nomihoshite oshimai
            So*2, Ra*4, Si*4, Do*4, Ky, Do*4, Ky, Do*4, Do*4, Ky,                                                                       // itsumo pyon pyon kanou
            Si*4, No, Si*4, Si*4, Ra*4, Ra*4, So*2, Ra*4, So*2, Fa*2,                                                                   // tanoshisa motomete
            Mi*2, No, Si*4, No, Mi*2, No, Ky, Si*4, No, Si*4, Do*4, Si*4, Ra*4, So*2,                                                   // mou chotto hajike chae
            So*2, No, Fa*2, So*2, Ra*4, Ky, Ra*4, Ky, Ra*4, Ra*4, Ky, So*2, No, So*2, So*2, Si*4, Do*4, Ky, Ky,                         // pyon pyon to issho nara suteki dai
            Fa*2, So*2, Ra*4, So*2, Mi*2, Ra*4, So*2, Mi*2, Do*4, Si*4, No, Si*4, So*2, So*2, So*4, Ky,                                 // kimi ni iwasetai kara iinasai
            So*2, Ra*4, Si*2, Do*4, Ky, Do*4, Ky, Do*4, Do*4, Ky, Si*4, Si*4, Si*4, Ra*4, Ra*4, So*2, Ra*4, So*2, Mi*2,                 // kokoro pyon pyon machi kangaeru furishite
            Mi*2, Ky, Si*4, Ky, Mi*2, Ky, Ky, Si*4, No, Si*4, Do*4, Si*4, Ra*4, So*2, So*2, Fa*2, So*2,                                 // mou chotto chikazuichae pyon pyon to
            Ra*4, Ky, Ra*4, Ky, Ra*4, Ra*4, Ky, So*2, No, So*2, So*2, Si*4, Do*4, Ky, Ky,                                               // kantan niha oshienai
            Fa*2, So*2, Ra*4, So*2, Mi*2, Ra*4, So*2, Mi*2, Do*4, Si*4, No, Si*4,                                                       // konnani sukina koto ha
            mSo*2, mSo*2, mSo*2, Fa*2, So*2, Ra*4, Ra*4, Si*4, No, Si*4, Si*4, Si*4, Si*4, Si*4, Si*4, Do*4, Si*4, No, No, Si*4, No, No // suki datte koto ha wawawa naisho nano-
            };

#endif
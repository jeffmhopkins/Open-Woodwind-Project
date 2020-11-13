// Open Woodwind Project - Full
// Integrating controller and synth into one firmware
//
// Initial commit - JHopkins 11/12/2020 - Added in Synth v2 block diagram and initialization code base
//


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     cv_osc2345_detune_range; //xy=186.45054626464844,1894.0217475891113
AudioSynthWaveformDc     cv_oscillator2_detune;            //xy=278.94459533691406,1668.8017892837524
AudioSynthWaveformDc     cv_oscillator5_detune; //xy=292.15845108032227,2214.2302198410034
AudioEffectMultiply      m21; //xy=457.1652297973633,1676.4509868621826
AudioSynthWaveformDc     cv_oscillator3_detune; //xy=469.44415283203125,1850.230131149292
AudioSynthNoisePink      pink_jitter;          //xy=490.07117462158203,515.5156421661377
AudioSynthWaveformDc     cv_oscillator4_detune; //xy=487.01554107666016,1950.3730115890503
AudioSynthWaveformDc     cv_lfo2_shape; //xy=503.5157928466797,628.5158710479736
AudioSynthWaveformDc     cv_lfo1_shape; //xy=506.51610946655273,443.51582431793213
AudioEffectMultiply      m24; //xy=500.0224266052246,2206.4509773254395
AudioSynthWaveformDc     cv_lfo2_frequency; //xy=514.5157852172852,588.5158710479736
AudioSynthWaveformDc     cv_lfo1_frequency;            //xy=517.5161018371582,405.51582431793213
AudioSynthWaveformDc     cv_lfo1_jitter_amount; //xy=526.515625,479.515625
AudioSynthWaveformDc     cv_lfo2_jitter_amount; //xy=526.5156021118164,551.5155811309814
AudioEffectMultiply      m22; //xy=662.8795166015625,1869.3080472946167
AudioEffectMultiply      m23; //xy=665.879508972168,1925.0223817825317
AudioSynthWaveformModulated lfo2;  //xy=677.5157585144043,615.5159015655518
AudioSynthWaveformModulated lfo1;   //xy=694.5161170959473,427.5158863067627
AudioEffectMultiply      m4; //xy=708.9600791931152,544.5155982971191
AudioEffectMultiply      m3;      //xy=710.5156593322754,486.5156421661377
AudioSynthWaveformDc     cv_lfo_to_osc1_pitch_range; //xy=773.5159225463867,976.5158319473267
AudioSynthWaveformDc     cv_oscillator1_shape_modulation; //xy=774.51611328125,1157.515938282013
AudioSynthWaveformDc     cv_lfo_to_osc1_shape_range;  //xy=775.5156173706055,1197.5158920288086
AudioSynthWaveformDc     cv_lfo_to_osc2345_pitch_range; //xy=776.0155639648438,1450.5158081054688
AudioSynthWaveformDc     cv_lfo_to_osc2345_shape_range; //xy=788.0155181884766,1694.5158367156982
AudioSynthWaveformDc     cv_pitchbend2_range; //xy=794.0158042907715,296.5156259536743
AudioSynthWaveformDc     cv_pitchbend1_range; //xy=794.5159721374512,260.5156669616699
AudioSynthWaveformDc     cv_pitchbend2_amount; //xy=798.516056060791,333.5156545639038
AudioSynthWaveformDc     cv_pitchbend1_amount; //xy=800.5159645080566,224.5156955718994
AudioSynthWaveformDc     cv_keyed_frequency_multiplier;            //xy=823.0003929138184,189.5156660079956
AudioMixer4              lfo1_mixer;         //xy=854.5157508850098,447.51580810546875
AudioMixer4              lfo2_mixer; //xy=857.5156898498535,563.5157794952393
AudioSynthWaveformDc     cv_lfo1_to_osc1_pitch_amount; //xy=941.5156478881836,1051.5156269073486
AudioSynthWaveformDc     cv_lfo2_to_osc1_pitch_amount;  //xy=943.5158920288086,1086.5156335830688
AudioSynthWaveformDc     cv_lfo1_to_osc2345_pitch_amount; //xy=944.0152893066406,1525.5156030654907
AudioSynthWaveformDc     cv_lfo2_to_osc2345_pitch_amount; //xy=946.0155334472656,1560.515609741211
AudioSynthWaveformDc     cv_lfo1_to_osc1_shape_amount; //xy=956.5157089233398,1271.5156364440918
AudioSynthWaveformDc     cv_lfo1_to_osc2345_shape_amount; //xy=956.0152435302734,1769.5156316757202
AudioSynthWaveformDc     cv_lfo2_to_osc1_shape_amount; //xy=958.5155868530273,1308.5156927108765
AudioSynthWaveformDc     cv_lfo2_to_osc2345_shape_amount; //xy=958.0154876708984,1804.5156383514404
AudioEffectMultiply      m1;      //xy=983.515983581543,230.5156650543213
AudioEffectMultiply      m2; //xy=984.51611328125,302.5156841278076
AudioEffectMultiply      m5; //xy=1029.5160217285156,971.515664100647
AudioEffectMultiply      m6; //xy=1030.5156860351562,1015.5156936645508
AudioEffectMultiply      m9; //xy=1031.5157165527344,1192.515724182129
AudioEffectMultiply      m10; //xy=1032.515380859375,1236.5157537460327
AudioEffectMultiply      m13; //xy=1032.0156631469727,1445.515640258789
AudioEffectMultiply      m14; //xy=1033.0153274536133,1489.5156698226929
AudioEffectMultiply      m17; //xy=1044.0156173706055,1689.5156688690186
AudioEffectMultiply      m18; //xy=1045.015281677246,1733.5156984329224
AudioSynthWaveformDc     cv_oscillator3_shape_modulation; //xy=1124.0157470703125,1909.5160627365112
AudioSynthWaveformDc     cv_oscillator4_shape_modulation; //xy=1130.0157470703125,2112.5160627365112
AudioSynthWaveformDc     cv_oscillator5_shape_modulation; //xy=1131.0157470703125,2283.5160627365112
AudioSynthWaveformDc     cv_oscillator2_shape_modulation; //xy=1152.5161209106445,1639.5162553787231
AudioMixer4              pitch_mixer;         //xy=1174.515998840332,207.5157012939453
AudioEffectMultiply      m7; //xy=1197.5157775878906,981.5156946182251
AudioEffectMultiply      m8; //xy=1197.5155334472656,1026.5156984329224
AudioEffectMultiply      m11; //xy=1199.5154724121094,1202.515754699707
AudioEffectMultiply      m12; //xy=1199.5152282714844,1247.5157585144043
AudioEffectMultiply      m15; //xy=1200.0154190063477,1455.5156707763672
AudioEffectMultiply      m16; //xy=1200.0151748657227,1500.5156745910645
AudioEffectMultiply      m19; //xy=1212.0153732299805,1699.5156993865967
AudioEffectMultiply      m20; //xy=1212.0151290893555,1744.515703201294
AudioMixer4              oscillator2_pitch_mixer; //xy=1426.5159072875977,1519.515775680542
AudioMixer4              oscillator1_pitch_mixer; //xy=1429.2814331054688,987.2814521789551
AudioMixer4              oscillator2_shape_mixer; //xy=1428.5158767700195,1694.5161418914795
AudioMixer4              oscillator3_pitch_mixer; //xy=1432.0154113769531,1862.515323638916
AudioMixer4              oscillator1_shape_mixer; //xy=1437.5159606933594,1180.515817642212
AudioMixer4              oscillator3_shape_mixer; //xy=1437.0154418945312,1930.5158462524414
AudioMixer4              oscillator4_pitch_mixer; //xy=1438.0154113769531,2065.515323638916
AudioMixer4              oscillator5_pitch_mixer; //xy=1439.0154113769531,2236.515323638916
AudioMixer4              oscillator4_shape_mixer; //xy=1443.0154418945312,2133.5158462524414
AudioMixer4              oscillator5_shape_mixer; //xy=1444.0154418945312,2304.5158462524414
AudioSynthWaveformModulated oscillator2; //xy=1661.5161209106445,1578.516077041626
AudioSynthWaveformModulated oscillator3; //xy=1667.015625,1921.515625
AudioSynthWaveformModulated oscillator1;   //xy=1670.7502460479736,993.7501192092896
AudioSynthWaveformModulated oscillator4; //xy=1673.015625,2124.515625
AudioSynthWaveformModulated oscillator5; //xy=1674.015625,2295.515625
AudioSynthWaveformDc     cv_oscillator2_gain; //xy=1680.515769958496,1624.5157842636108
AudioSynthWaveformDc     cv_lfo1_to_filter_amount; //xy=1691.2223892211914,798.7380709648132
AudioSynthWaveformDc     cv_oscillator1_gain; //xy=1691.1284103393555,1043.906229019165
AudioSynthWaveformDc     cv_lfo2_to_filter_amount;  //xy=1692.5628814697266,844.6745548248291
AudioSynthWaveformDc     cv_oscillator3_gain; //xy=1688.5152587890625,1966.5151357650757
AudioSynthWaveformDc     cv_oscillator5_gain; //xy=1694.5152587890625,2338.5151357650757
AudioSynthWaveformDc     cv_oscillator4_gain; //xy=1703.5152587890625,2172.5151357650757
AudioEffectMultiply      m26; //xy=1865.5161361694336,1585.5162734985352
AudioEffectMultiply      m27; //xy=1873.515625,1927.515625
AudioEffectMultiply      m25;      //xy=1878.90625,1017.2395833333333
AudioEffectMultiply      m29; //xy=1879.515625,2299.515625
AudioEffectMultiply      m28; //xy=1888.515625,2133.515625
AudioSynthWaveformDc     cv_1v; //xy=2002.1287155151367,387.23967361450195
AudioEffectMultiply      m32; //xy=2058.2062225341797,787.5315504074097
AudioEffectMultiply      m33; //xy=2058.705368041992,827.5314741134644
AudioSynthWaveformDc     cv_white_noise_gain; //xy=2132.5157203674316,1075.515640258789
AudioSynthWaveformDc     cv_pink_noise_gain; //xy=2136.51570892334,1187.5156784057617
AudioMixer4              oscillator_mixer;         //xy=2154.515968322754,1019.5157012939453
AudioSynthWaveformDc     cv_filter_frequency_amount; //xy=2166.8980865478516,729.6904544830322
AudioMixer4              oscillator2345_mixer; //xy=2168.5158920288086,2016.5159673690796
AudioSynthNoisePink      pink;          //xy=2172.7668647766113,1148.266254901886
AudioSynthNoiseWhite     noise;         //xy=2174.9336128234863,1111.932674407959
AudioSynthWaveformDc     cv_oscillator2345_gain; //xy=2172.5157470703125,2084.515685081482
AudioSynthWaveformDc     cv_lfo1_to_vca_amount; //xy=2211.0167808532715,500.5157551765442
AudioSynthWaveformDc     cv_lfo2_to_vca_amount; //xy=2211.515926361084,605.5156788825989
AudioMixer4              lfo_to_filter_mixer1; //xy=2228.2064666748047,793.5318698883057
AudioEffectMultiply      m36; //xy=2287.5712280273438,1092.626745223999
AudioSynthWaveformDc     cv_filter_frequency_offset; //xy=2289.396926879883,867.5793704986572
AudioEffectMultiply      m37; //xy=2294.793399810791,1169.0712184906006
AudioEffectMultiply      m34;      //xy=2387.7953872680664,748.3508052825928
AudioEffectMultiply      m38;      //xy=2400.5158309936523,2023.5159673690796
AudioEffectMultiply      m30; //xy=2407.0165100097656,480.515661239624
AudioEffectMultiply      m31; //xy=2407.515655517578,585.5155849456787
AudioMixer4              lfo_to_filter_mixer2; //xy=2530.017349243164,808.3507976531982
AudioMixer4              pre_filter_mixer; //xy=2532.015926361084,1038.5157356262207
AudioPlaySdWav           playSdWav1;     //xy=2569.0877838134766,2032.659161567688
AudioInputI2S2           input;         //xy=2581.088150024414,1998.659315109253
AudioSynthWaveformDc     cv_vca_modulation; //xy=2588.2937927246094,413.73790740966797
AudioMixer4              lfo_to_vca_mixer; //xy=2614.5157775878906,491.51569175720215
AudioFilterStateVariable filter;        //xy=2700.5170936584473,1006.5158500671387
AudioEffectMultiply      m35; //xy=2783.2395820617676,456.12846851348877
AudioMixer4              pre_vca_mixer;         //xy=2860.5161170959473,1025.5157890319824
AudioMixer4              input_mixer;         //xy=2913.6591033935547,1989.5162315368652
AudioEffectMultiply      vca;      //xy=3048.5169105529785,1017.5158805847168
AudioMixer4              pre_flange_mixer;         //xy=3202.5163230895996,1102.5157585144043
AudioEffectFlange        flange1;        //xy=3364.129421234131,1181.2940101623535
AudioMixer4              pre_chorus_mixer; //xy=3489.4612731933594,1117.1826763153076
AudioEffectChorus        chorus1;        //xy=3602.6830825805664,1204.8490924835205
AudioMixer4              pre_waveshape_mixer; //xy=3763.1827239990234,1139.1823463439941
AudioEffectWaveshaper    waveshape1;     //xy=3929.627021789551,1222.1823997497559
AudioMixer4              pre_delay_mixer; //xy=4098.515785217285,1161.2934303283691
AudioMixer4              delay_mixer1; //xy=4320.016448974609,1176.5159187316895
AudioEffectDelay         delay1;         //xy=4500.573146820068,1439.0716285705566
AudioEffectFreeverbStereo reverb;     //xy=4561.073719024658,1165.5161714553833
AudioMixer4              delay_mixer3; //xy=4650.350433349609,1467.849292755127
AudioMixer4              delay_mixer2; //xy=4652.350189208984,1405.849323272705
AudioMixer4              left;         //xy=4691.073841094971,1114.5161399841309
AudioMixer4              right;         //xy=4701.073596954346,1217.5160789489746
AudioOutputI2S           i2s1_out;           //xy=4834.0737228393555,1167.5161399841309
AudioConnection          patchCord1(cv_osc2345_detune_range, 0, m22, 1);
AudioConnection          patchCord2(cv_osc2345_detune_range, 0, m21, 1);
AudioConnection          patchCord3(cv_osc2345_detune_range, 0, m23, 0);
AudioConnection          patchCord4(cv_osc2345_detune_range, 0, m24, 0);
AudioConnection          patchCord5(cv_oscillator2_detune, 0, m21, 0);
AudioConnection          patchCord6(cv_oscillator5_detune, 0, m24, 1);
AudioConnection          patchCord7(m21, 0, oscillator2_pitch_mixer, 3);
AudioConnection          patchCord8(cv_oscillator3_detune, 0, m22, 0);
AudioConnection          patchCord9(pink_jitter, 0, m3, 1);
AudioConnection          patchCord10(pink_jitter, 0, m4, 0);
AudioConnection          patchCord11(cv_oscillator4_detune, 0, m23, 1);
AudioConnection          patchCord12(cv_lfo2_shape, 0, lfo2, 1);
AudioConnection          patchCord13(cv_lfo1_shape, 0, lfo1, 1);
AudioConnection          patchCord14(m24, 0, oscillator5_pitch_mixer, 3);
AudioConnection          patchCord15(cv_lfo2_frequency, 0, lfo2, 0);
AudioConnection          patchCord16(cv_lfo1_frequency, 0, lfo1, 0);
AudioConnection          patchCord17(cv_lfo1_jitter_amount, 0, m3, 0);
AudioConnection          patchCord18(cv_lfo2_jitter_amount, 0, m4, 1);
AudioConnection          patchCord19(m22, 0, oscillator3_pitch_mixer, 3);
AudioConnection          patchCord20(m23, 0, oscillator4_pitch_mixer, 3);
AudioConnection          patchCord21(lfo2, 0, lfo2_mixer, 1);
AudioConnection          patchCord22(lfo1, 0, lfo1_mixer, 0);
AudioConnection          patchCord23(m4, 0, lfo2_mixer, 0);
AudioConnection          patchCord24(m3, 0, lfo1_mixer, 1);
AudioConnection          patchCord25(cv_lfo_to_osc1_pitch_range, 0, m5, 1);
AudioConnection          patchCord26(cv_lfo_to_osc1_pitch_range, 0, m6, 1);
AudioConnection          patchCord27(cv_oscillator1_shape_modulation, 0, oscillator1_shape_mixer, 0);
AudioConnection          patchCord28(cv_lfo_to_osc1_shape_range, 0, m9, 1);
AudioConnection          patchCord29(cv_lfo_to_osc1_shape_range, 0, m10, 1);
AudioConnection          patchCord30(cv_lfo_to_osc2345_pitch_range, 0, m13, 1);
AudioConnection          patchCord31(cv_lfo_to_osc2345_pitch_range, 0, m14, 1);
AudioConnection          patchCord32(cv_lfo_to_osc2345_shape_range, 0, m17, 1);
AudioConnection          patchCord33(cv_lfo_to_osc2345_shape_range, 0, m18, 1);
AudioConnection          patchCord34(cv_pitchbend2_range, 0, m2, 0);
AudioConnection          patchCord35(cv_pitchbend1_range, 0, m1, 1);
AudioConnection          patchCord36(cv_pitchbend2_amount, 0, m2, 1);
AudioConnection          patchCord37(cv_pitchbend1_amount, 0, m1, 0);
AudioConnection          patchCord38(cv_keyed_frequency_multiplier, 0, pitch_mixer, 0);
AudioConnection          patchCord39(lfo1_mixer, 0, m32, 0);
AudioConnection          patchCord40(lfo1_mixer, 0, m5, 0);
AudioConnection          patchCord41(lfo1_mixer, 0, m9, 0);
AudioConnection          patchCord42(lfo1_mixer, 0, m13, 0);
AudioConnection          patchCord43(lfo1_mixer, 0, m17, 0);
AudioConnection          patchCord44(lfo1_mixer, 0, m30, 0);
AudioConnection          patchCord45(lfo2_mixer, 0, m31, 0);
AudioConnection          patchCord46(lfo2_mixer, 0, m33, 0);
AudioConnection          patchCord47(lfo2_mixer, 0, m6, 0);
AudioConnection          patchCord48(lfo2_mixer, 0, m10, 0);
AudioConnection          patchCord49(lfo2_mixer, 0, m14, 0);
AudioConnection          patchCord50(lfo2_mixer, 0, m18, 0);
AudioConnection          patchCord51(cv_lfo1_to_osc1_pitch_amount, 0, m7, 1);
AudioConnection          patchCord52(cv_lfo2_to_osc1_pitch_amount, 0, m8, 1);
AudioConnection          patchCord53(cv_lfo1_to_osc2345_pitch_amount, 0, m15, 1);
AudioConnection          patchCord54(cv_lfo2_to_osc2345_pitch_amount, 0, m16, 1);
AudioConnection          patchCord55(cv_lfo1_to_osc2345_shape_amount, 0, m19, 1);
AudioConnection          patchCord56(cv_lfo2_to_osc1_shape_amount, 0, m11, 1);
AudioConnection          patchCord57(cv_lfo2_to_osc1_shape_amount, 0, m12, 1);
AudioConnection          patchCord58(cv_lfo2_to_osc2345_shape_amount, 0, m20, 1);
AudioConnection          patchCord59(m1, 0, pitch_mixer, 1);
AudioConnection          patchCord60(m2, 0, pitch_mixer, 2);
AudioConnection          patchCord61(m5, 0, m7, 0);
AudioConnection          patchCord62(m6, 0, m8, 0);
AudioConnection          patchCord63(m9, 0, m11, 0);
AudioConnection          patchCord64(m10, 0, m12, 0);
AudioConnection          patchCord65(m13, 0, m15, 0);
AudioConnection          patchCord66(m14, 0, m16, 0);
AudioConnection          patchCord67(m17, 0, m19, 0);
AudioConnection          patchCord68(m18, 0, m20, 0);
AudioConnection          patchCord69(cv_oscillator3_shape_modulation, 0, oscillator3_shape_mixer, 0);
AudioConnection          patchCord70(cv_oscillator4_shape_modulation, 0, oscillator4_shape_mixer, 0);
AudioConnection          patchCord71(cv_oscillator5_shape_modulation, 0, oscillator5_shape_mixer, 0);
AudioConnection          patchCord72(cv_oscillator2_shape_modulation, 0, oscillator2_shape_mixer, 0);
AudioConnection          patchCord73(pitch_mixer, 0, oscillator1_pitch_mixer, 0);
AudioConnection          patchCord74(pitch_mixer, 0, oscillator2_pitch_mixer, 0);
AudioConnection          patchCord75(pitch_mixer, 0, oscillator3_pitch_mixer, 0);
AudioConnection          patchCord76(pitch_mixer, 0, oscillator4_pitch_mixer, 0);
AudioConnection          patchCord77(pitch_mixer, 0, oscillator5_pitch_mixer, 0);
AudioConnection          patchCord78(m7, 0, oscillator1_pitch_mixer, 1);
AudioConnection          patchCord79(m8, 0, oscillator1_pitch_mixer, 2);
AudioConnection          patchCord80(m11, 0, oscillator1_shape_mixer, 1);
AudioConnection          patchCord81(m12, 0, oscillator1_shape_mixer, 2);
AudioConnection          patchCord82(m15, 0, oscillator2_pitch_mixer, 1);
AudioConnection          patchCord83(m15, 0, oscillator3_pitch_mixer, 1);
AudioConnection          patchCord84(m15, 0, oscillator4_pitch_mixer, 1);
AudioConnection          patchCord85(m15, 0, oscillator5_pitch_mixer, 1);
AudioConnection          patchCord86(m16, 0, oscillator2_pitch_mixer, 2);
AudioConnection          patchCord87(m16, 0, oscillator3_pitch_mixer, 2);
AudioConnection          patchCord88(m16, 0, oscillator4_pitch_mixer, 2);
AudioConnection          patchCord89(m16, 0, oscillator5_pitch_mixer, 2);
AudioConnection          patchCord90(m19, 0, oscillator2_shape_mixer, 1);
AudioConnection          patchCord91(m19, 0, oscillator3_shape_mixer, 1);
AudioConnection          patchCord92(m19, 0, oscillator4_shape_mixer, 1);
AudioConnection          patchCord93(m19, 0, oscillator5_shape_mixer, 1);
AudioConnection          patchCord94(m20, 0, oscillator2_shape_mixer, 2);
AudioConnection          patchCord95(m20, 0, oscillator3_shape_mixer, 2);
AudioConnection          patchCord96(m20, 0, oscillator4_shape_mixer, 2);
AudioConnection          patchCord97(m20, 0, oscillator5_shape_mixer, 2);
AudioConnection          patchCord98(oscillator2_pitch_mixer, 0, oscillator2, 0);
AudioConnection          patchCord99(oscillator1_pitch_mixer, 0, oscillator1, 0);
AudioConnection          patchCord100(oscillator2_shape_mixer, 0, oscillator2, 1);
AudioConnection          patchCord101(oscillator3_pitch_mixer, 0, oscillator3, 0);
AudioConnection          patchCord102(oscillator1_shape_mixer, 0, oscillator1, 1);
AudioConnection          patchCord103(oscillator3_shape_mixer, 0, oscillator3, 1);
AudioConnection          patchCord104(oscillator4_pitch_mixer, 0, oscillator4, 0);
AudioConnection          patchCord105(oscillator5_pitch_mixer, 0, oscillator5, 0);
AudioConnection          patchCord106(oscillator4_shape_mixer, 0, oscillator4, 1);
AudioConnection          patchCord107(oscillator5_shape_mixer, 0, oscillator5, 1);
AudioConnection          patchCord108(oscillator2, 0, m26, 0);
AudioConnection          patchCord109(oscillator3, 0, m27, 0);
AudioConnection          patchCord110(oscillator1, 0, m25, 0);
AudioConnection          patchCord111(oscillator4, 0, m28, 0);
AudioConnection          patchCord112(oscillator5, 0, m29, 0);
AudioConnection          patchCord113(cv_oscillator2_gain, 0, m26, 1);
AudioConnection          patchCord114(cv_lfo1_to_filter_amount, 0, m32, 1);
AudioConnection          patchCord115(cv_oscillator1_gain, 0, m25, 1);
AudioConnection          patchCord116(cv_lfo2_to_filter_amount, 0, m33, 1);
AudioConnection          patchCord117(cv_oscillator3_gain, 0, m27, 1);
AudioConnection          patchCord118(cv_oscillator5_gain, 0, m29, 1);
AudioConnection          patchCord119(cv_oscillator4_gain, 0, m28, 1);
AudioConnection          patchCord120(m26, 0, oscillator2345_mixer, 0);
AudioConnection          patchCord121(m27, 0, oscillator2345_mixer, 1);
AudioConnection          patchCord122(m25, 0, oscillator_mixer, 0);
AudioConnection          patchCord123(m29, 0, oscillator2345_mixer, 3);
AudioConnection          patchCord124(m28, 0, oscillator2345_mixer, 2);
AudioConnection          patchCord125(cv_1v, 0, lfo_to_vca_mixer, 0);
AudioConnection          patchCord126(cv_1v, 0, lfo_to_filter_mixer1, 0);
AudioConnection          patchCord127(m32, 0, lfo_to_filter_mixer1, 1);
AudioConnection          patchCord128(m33, 0, lfo_to_filter_mixer1, 2);
AudioConnection          patchCord129(cv_white_noise_gain, 0, m36, 0);
AudioConnection          patchCord130(cv_pink_noise_gain, 0, m37, 1);
AudioConnection          patchCord131(oscillator_mixer, 0, pre_filter_mixer, 0);
AudioConnection          patchCord132(cv_filter_frequency_amount, 0, m34, 0);
AudioConnection          patchCord133(oscillator2345_mixer, 0, m38, 0);
AudioConnection          patchCord134(pink, 0, m37, 0);
AudioConnection          patchCord135(noise, 0, m36, 1);
AudioConnection          patchCord136(cv_oscillator2345_gain, 0, m38, 1);
AudioConnection          patchCord137(cv_lfo1_to_vca_amount, 0, m30, 1);
AudioConnection          patchCord138(cv_lfo2_to_vca_amount, 0, m31, 1);
AudioConnection          patchCord139(lfo_to_filter_mixer1, 0, m34, 1);
AudioConnection          patchCord140(m36, 0, pre_filter_mixer, 1);
AudioConnection          patchCord141(cv_filter_frequency_offset, 0, lfo_to_filter_mixer2, 1);
AudioConnection          patchCord142(m37, 0, pre_filter_mixer, 2);
AudioConnection          patchCord143(m34, 0, lfo_to_filter_mixer2, 0);
AudioConnection          patchCord144(m38, 0, oscillator_mixer, 1);
AudioConnection          patchCord145(m30, 0, lfo_to_vca_mixer, 1);
AudioConnection          patchCord146(m31, 0, lfo_to_vca_mixer, 2);
AudioConnection          patchCord147(lfo_to_filter_mixer2, 0, filter, 0);
AudioConnection          patchCord148(pre_filter_mixer, 0, filter, 1);
AudioConnection          patchCord149(pre_filter_mixer, 0, pre_vca_mixer, 3);
AudioConnection          patchCord150(pre_filter_mixer, 0, pre_flange_mixer, 2);
AudioConnection          patchCord151(playSdWav1, 0, input_mixer, 2);
AudioConnection          patchCord152(playSdWav1, 0, left, 3);
AudioConnection          patchCord153(playSdWav1, 1, input_mixer, 3);
AudioConnection          patchCord154(playSdWav1, 1, right, 3);
AudioConnection          patchCord155(input, 0, input_mixer, 0);
AudioConnection          patchCord156(input, 0, left, 2);
AudioConnection          patchCord157(input, 1, input_mixer, 1);
AudioConnection          patchCord158(input, 1, right, 2);
AudioConnection          patchCord159(cv_vca_modulation, 0, m35, 0);
AudioConnection          patchCord160(lfo_to_vca_mixer, 0, m35, 1);
AudioConnection          patchCord161(filter, 0, pre_vca_mixer, 0);
AudioConnection          patchCord162(filter, 1, pre_vca_mixer, 1);
AudioConnection          patchCord163(filter, 2, pre_vca_mixer, 2);
AudioConnection          patchCord164(m35, 0, vca, 0);
AudioConnection          patchCord165(pre_vca_mixer, 0, vca, 1);
AudioConnection          patchCord166(pre_vca_mixer, 0, pre_flange_mixer, 1);
AudioConnection          patchCord167(input_mixer, 0, pre_flange_mixer, 3);
AudioConnection          patchCord168(input_mixer, 0, pre_filter_mixer, 3);
AudioConnection          patchCord169(vca, 0, pre_flange_mixer, 0);
AudioConnection          patchCord170(pre_flange_mixer, flange1);
AudioConnection          patchCord171(pre_flange_mixer, 0, pre_chorus_mixer, 0);
AudioConnection          patchCord172(flange1, 0, pre_chorus_mixer, 1);
AudioConnection          patchCord173(pre_chorus_mixer, 0, pre_waveshape_mixer, 0);
AudioConnection          patchCord174(pre_chorus_mixer, chorus1);
AudioConnection          patchCord175(chorus1, 0, pre_waveshape_mixer, 1);
AudioConnection          patchCord176(pre_waveshape_mixer, 0, pre_delay_mixer, 0);
AudioConnection          patchCord177(pre_waveshape_mixer, waveshape1);
AudioConnection          patchCord178(waveshape1, 0, pre_delay_mixer, 1);
AudioConnection          patchCord179(pre_delay_mixer, 0, delay_mixer1, 0);
AudioConnection          patchCord180(delay_mixer1, delay1);
AudioConnection          patchCord181(delay_mixer1, reverb);
AudioConnection          patchCord182(delay_mixer1, 0, left, 0);
AudioConnection          patchCord183(delay_mixer1, 0, right, 0);
AudioConnection          patchCord184(delay1, 0, delay_mixer2, 0);
AudioConnection          patchCord185(delay1, 1, delay_mixer2, 1);
AudioConnection          patchCord186(delay1, 2, delay_mixer2, 2);
AudioConnection          patchCord187(delay1, 3, delay_mixer2, 3);
AudioConnection          patchCord188(delay1, 4, delay_mixer3, 0);
AudioConnection          patchCord189(delay1, 5, delay_mixer3, 1);
AudioConnection          patchCord190(delay1, 6, delay_mixer3, 2);
AudioConnection          patchCord191(delay1, 7, delay_mixer3, 3);
AudioConnection          patchCord192(reverb, 0, left, 1);
AudioConnection          patchCord193(reverb, 1, right, 1);
AudioConnection          patchCord194(delay_mixer3, 0, delay_mixer1, 2);
AudioConnection          patchCord195(delay_mixer2, 0, delay_mixer1, 1);
AudioConnection          patchCord196(left, 0, i2s1_out, 0);
AudioConnection          patchCord197(right, 0, i2s1_out, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=4676.1848068237305,1013.5161666870117
// GUItool: end automatically generated code



float master_volume = 0.8;
float eq_1          = 0.0;
float eq_2          = 0.0;
float eq_3          = 0.0;
float eq_4          = 0.0;
float eq_5          = 0.0;
float filter_frequency = 440.0;
float filter_octaves   = 5; //1 = +5 octaves, -1 = -5 octaves
float filter_resonance = 0.707;
float oscillator_frequency = 440;
float oscillator_octaves   = 5;
float SEMITONE             = 1.0/(oscillator_octaves * 12.0);

//Flange specific
#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
short   delayline[FLANGE_DELAY_LENGTH];
int     s_idx   = FLANGE_DELAY_LENGTH/4;
int     s_depth = FLANGE_DELAY_LENGTH/4;
double  s_freq  = .5;

//Chorus specific
#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)
short   chorus_delayline[CHORUS_DELAY_LENGTH];
int     n_chorus = 4;

//Waveshape specific
const float wave_shape_tube_12ax7_1025[1025] = {-0.9998356,-0.9998321,-0.9998285,-0.9998249,-0.9998211,-0.9998172,-0.9998131,-0.999809,-0.9998046,-0.9998002,-0.9997956,-0.9997908,-0.9997859,-0.9997808,-0.9997756,-0.9997702,-0.9997646,-0.9997588,-0.9997528,-0.9997466,-0.9997402,-0.9997337,-0.9997269,-0.9997199,-0.9997126,-0.9997051,-0.9996973,-0.9996893,-0.9996811,-0.9996725,-0.9996637,-0.9996545,-0.9996451,-0.9996354,-0.9996254,-0.999615,-0.9996043,-0.9995932,-0.9995818,-0.99957,-0.9995577,-0.9995452,-0.9995321,-0.9995187,-0.9995048,-0.9994904,-0.9994756,-0.9994603,-0.9994445,-0.9994282,-0.9994113,-0.9993939,-0.9993759,-0.9993573,-0.9993382,-0.9993184,-0.9992979,-0.9992768,-0.999255,-0.9992325,-0.9992092,-0.9991852,-0.9991604,-0.9991348,-0.9991084,-0.999081,-0.9990528,-0.9990237,-0.9989937,-0.9989626,-0.9989306,-0.9988975,-0.9988633,-0.9988281,-0.9987917,-0.9987541,-0.9987153,-0.9986753,-0.998634,-0.9985913,-0.9985473,-0.9985018,-0.9984549,-0.9984065,-0.9983565,-0.998305,-0.9982517,-0.9981968,-0.9981401,-0.9980816,-0.9980212,-0.997959,-0.9978947,-0.9978284,-0.9977599,-0.9976894,-0.9976166,-0.9975415,-0.997464,-0.9973841,-0.9973016,-0.9972166,-0.997129,-0.9970385,-0.9969453,-0.9968491,-0.9967499,-0.9966477,-0.9965422,-0.9964335,-0.9963214,-0.9962059,-0.9960868,-0.995964,-0.9958375,-0.995707,-0.9955727,-0.9954342,-0.9952915,-0.9951445,-0.994993,-0.9948369,-0.9946762,-0.9945106,-0.9943401,-0.9941645,-0.9939836,-0.9937974,-0.9936056,-0.9934081,-0.9932048,-0.9929955,-0.9927801,-0.9925584,-0.9923303,-0.9920956,-0.9918541,-0.9916056,-0.99135,-0.9910871,-0.9908168,-0.9905387,-0.9902529,-0.9899589,-0.9896568,-0.9893463,-0.9890271,-0.9886991,-0.988362,-0.9880158,-0.98766,-0.9872945,-0.9869192,-0.9865337,-0.986138,-0.9857317,-0.9853147,-0.9848867,-0.9844475,-0.9839969,-0.9835346,-0.9830605,-0.9825742,-0.9820755,-0.9815643,-0.9810402,-0.980503,-0.9799525,-0.9793884,-0.9788105,-0.9782187,-0.9776124,-0.9769915,-0.9763558,-0.9757051,-0.9750391,-0.9743575,-0.9736603,-0.9729471,-0.9722176,-0.9714716,-0.9707089,-0.9699293,-0.9691325,-0.9683182,-0.9674864,-0.9666366,-0.9657687,-0.9648825,-0.9639778,-0.9630542,-0.9621117,-0.9611499,-0.9601685,-0.9591675,-0.9581466,-0.9571057,-0.9560446,-0.954963,-0.9538608,-0.9527378,-0.9515938,-0.9504287,-0.9492422,-0.9480343,-0.9468047,-0.9455533,-0.9442799,-0.9429844,-0.9416666,-0.9403264,-0.9389637,-0.9375783,-0.9361702,-0.9347389,-0.9332845,-0.9318069,-0.9303061,-0.928782,-0.9272345,-0.9256635,-0.9240688,-0.9224505,-0.9208084,-0.9191425,-0.9174528,-0.9157391,-0.9140013,-0.9122396,-0.9104538,-0.9086438,-0.9068097,-0.9049515,-0.903069,-0.9011623,-0.8992313,-0.8972758,-0.895296,-0.8932921,-0.8912638,-0.8892113,-0.8871346,-0.8850336,-0.8829085,-0.8807591,-0.8785856,-0.876388,-0.8741663,-0.8719205,-0.8696507,-0.867357,-0.8650392,-0.8626977,-0.8603323,-0.8579431,-0.8555301,-0.8530936,-0.8506331,-0.8481492,-0.8456417,-0.8431109,-0.8405568,-0.8379794,-0.8353788,-0.8327552,-0.8301086,-0.827439,-0.8247465,-0.8220314,-0.8192935,-0.8165331,-0.8137501,-0.8109448,-0.8081172,-0.8052673,-0.8023953,-0.7995013,-0.7965854,-0.7936474,-0.7906877,-0.7877063,-0.7847034,-0.781679,-0.7786333,-0.7755664,-0.7724784,-0.7693694,-0.7662394,-0.7630886,-0.7599171,-0.7567251,-0.7535125,-0.7502796,-0.7470264,-0.743753,-0.7404595,-0.7371461,-0.7338128,-0.7304597,-0.727087,-0.7236946,-0.7202827,-0.7168516,-0.7134012,-0.7099317,-0.7064433,-0.7029359,-0.6994097,-0.6958649,-0.6923015,-0.6887197,-0.6851195,-0.681501,-0.6778644,-0.6742097,-0.6705371,-0.6668467,-0.6631386,-0.6594127,-0.6556695,-0.6519088,-0.6481305,-0.644335,-0.6405225,-0.6366929,-0.6328464,-0.6289831,-0.6251031,-0.6212065,-0.6172934,-0.6133639,-0.6094181,-0.6054561,-0.6014779,-0.5974838,-0.5934737,-0.5894479,-0.5854063,-0.5813491,-0.5772763,-0.5731882,-0.5690847,-0.5649658,-0.5608317,-0.5566826,-0.5525185,-0.5483397,-0.5441459,-0.5399376,-0.5357146,-0.5314772,-0.5272254,-0.5229592,-0.5186789,-0.5143844,-0.510076,-0.5057536,-0.5014173,-0.4970673,-0.4927037,-0.4883265,-0.4839357,-0.4795317,-0.4751142,-0.4706835,-0.4662397,-0.4617828,-0.457313,-0.4528304,-0.4483351,-0.4438271,-0.4393066,-0.4347736,-0.4302283,-0.4256707,-0.4211009,-0.4165191,-0.4119253,-0.4073196,-0.4027022,-0.3980731,-0.3934324,-0.3887803,-0.3841168,-0.3794421,-0.3747562,-0.3700592,-0.3653513,-0.3606327,-0.3559033,-0.3511635,-0.3464133,-0.3416527,-0.3368821,-0.3321014,-0.3273109,-0.3225107,-0.317701,-0.3128818,-0.3080534,-0.303216,-0.2983698,-0.2935148,-0.2886515,-0.2837798,-0.2789001,-0.2740125,-0.2691173,-0.2642147,-0.2593051,-0.2543888,-0.249466,-0.244537,-0.2396021,-0.2346618,-0.2297163,-0.2247661,-0.2198115,-0.2148531,-0.2098912,-0.2049264,-0.1999592,-0.19499,-0.1900196,-0.1850484,-0.1800772,-0.1751067,-0.1701375,-0.1651704,-0.1602063,-0.155246,-0.1502904,-0.1453405,-0.1403972,-0.1354616,-0.1305348,-0.1256179,-0.1207122,-0.1158189,-0.1109393,-0.1060748,-0.1012267,-0.09639668,-0.09158609,-0.08679653,-0.0820296,-0.07728693,-0.0725702,-0.06788112,-0.06322179,-0.0585936,-0.05399832,-0.04943768,-0.04491345,-0.04042734,-0.03598107,-0.03157631,-0.02721469,-0.02289781,-0.01862717,-0.01440425,-0.01023041,-0.006106971,-0.002035128,0.001984002,0.005949407,0.009860178,0.01371552,0.01751473,0.02125725,0.02494214,0.02856926,0.03213862,0.03565009,0.03910363,0.04249933,0.04583734,0.04911792,0.05234143,0.05550827,0.05861896,0.06167405,0.06467417,0.06762,0.07051229,0.07335179,0.07613934,0.07887577,0.08156197,0.08419883,0.08678727,0.08932804,0.0918219,0.0942702,0.09667389,0.09903392,0.1013512,0.1036268,0.1058616,0.1080565,0.1102124,0.1123303,0.114411,0.1164554,0.1184645,0.120439,0.1223798,0.1242877,0.1261635,0.128008,0.129822,0.1316062,0.1333613,0.1350877,0.1367865,0.1384583,0.1401037,0.1417236,0.1433183,0.1448886,0.1464351,0.1479583,0.1494588,0.1509371,0.1523937,0.1538292,0.1552441,0.1566388,0.1580138,0.1593695,0.1607065,0.1620251,0.1633258,0.164609,0.1658749,0.1671239,0.1683566,0.1695733,0.1707743,0.1719601,0.1731308,0.1742869,0.1754286,0.1765563,0.1776702,0.1787707,0.1798581,0.1809325,0.1819943,0.1830437,0.184081,0.1851064,0.1861202,0.1871225,0.1881137,0.1890939,0.1900632,0.191022,0.1919705,0.1929088,0.1938372,0.1947558,0.1956649,0.1965645,0.1974549,0.1983363,0.1992088,0.2000726,0.2009277,0.2017745,0.202613,0.2034434,0.2042658,0.2050803,0.2058871,0.2066864,0.2074782,0.2082626,0.2090398,0.2098099,0.2105731,0.2113294,0.212079,0.2128219,0.2135584,0.2142884,0.2150122,0.2157297,0.2164411,0.2171465,0.2178459,0.2185396,0.2192274,0.2199097,0.2205863,0.2212575,0.2219233,0.2225837,0.2232389,0.2238888,0.2245337,0.2251736,0.2258085,0.2264386,0.2270638,0.2276843,0.2283001,0.2289114,0.229518,0.2301202,0.230718,0.2313115,0.2319006,0.2324855,0.2330662,0.2336428,0.2342153,0.2347838,0.2353484,0.235909,0.2364657,0.2370186,0.2375677,0.2381131,0.2386549,0.239193,0.2397276,0.2402586,0.2407861,0.2413102,0.2418309,0.2423482,0.2428622,0.243373,0.2438805,0.2443847,0.2448859,0.2453838,0.2458788,0.2463706,0.2468594,0.2473452,0.2478281,0.248308,0.2487851,0.2492593,0.2497307,0.2501993,0.2506652,0.2511283,0.2515888,0.2520466,0.2525018,0.2529543,0.2534043,0.2538517,0.2542966,0.254739,0.2551789,0.2556164,0.2560515,0.2564842,0.2569145,0.2573424,0.2577681,0.2581914,0.2586125,0.2590313,0.2594479,0.2598623,0.2602745,0.2606846,0.2610925,0.2614983,0.2619021,0.2623037,0.2627033,0.2631009,0.2634964,0.26389,0.2642815,0.2646712,0.2650589,0.2654446,0.2658285,0.2662105,0.2665906,0.2669688,0.2673452,0.2677199,0.2680927,0.2684637,0.268833,0.2692005,0.2695663,0.2699304,0.2702928,0.2706535,0.2710125,0.2713699,0.2717256,0.2720797,0.2724322,0.2727831,0.2731324,0.2734801,0.2738263,0.2741709,0.274514,0.2748556,0.2751956,0.2755342,0.2758713,0.2762069,0.2765411,0.2768738,0.2772051,0.277535,0.2778635,0.2781906,0.2785163,0.2788406,0.2791636,0.2794852,0.2798055,0.2801244,0.280442,0.2807584,0.2810734,0.2813871,0.2816995,0.2820107,0.2823206,0.2826293,0.2829368,0.2832429,0.2835479,0.2838517,0.2841543,0.2844557,0.2847559,0.285055,0.2853528,0.2856495,0.2859451,0.2862396,0.2865329,0.2868251,0.2871161,0.2874061,0.2876949,0.2879827,0.2882694,0.288555,0.2888395,0.289123,0.2894055,0.2896869,0.2899672,0.2902466,0.2905249,0.2908022,0.2910785,0.2913538,0.2916281,0.2919015,0.2921738,0.2924452,0.2927156,0.2929851,0.2932535,0.2935211,0.2937877,0.2940534,0.2943181,0.2945819,0.2948449,0.2951069,0.295368,0.2956282,0.2958875,0.296146,0.2964036,0.2966602,0.2969161,0.297171,0.2974252,0.2976784,0.2979308,0.2981824,0.2984332,0.2986831,0.2989322,0.2991804,0.2994279,0.2996746,0.2999204,0.3001655,0.3004098,0.3006532,0.3008959,0.3011379,0.301379,0.3016194,0.301859,0.3020979,0.302336,0.3025734,0.30281,0.3030459,0.303281,0.3035154,0.3037491,0.3039821,0.3042143,0.3044459,0.3046767,0.3049068,0.3051362,0.3053649,0.305593,0.3058203,0.306047,0.306273,0.3064983,0.3067229,0.3069468,0.3071702,0.3073928,0.3076148,0.3078361,0.3080568,0.3082768,0.3084962,0.308715,0.3089331,0.3091505,0.3093674,0.3095836,0.3097993,0.3100142,0.3102286,0.3104424,0.3106556,0.3108681,0.3110801,0.3112915,0.3115022,0.3117124,0.311922,0.312131,0.3123395,0.3125473,0.3127546,0.3129613,0.3131674,0.313373,0.313578,0.3137825,0.3139863,0.3141897,0.3143924,0.3145947,0.3147964,0.3149976,0.3151982,0.3153982,0.3155978,0.3157968,0.3159953,0.3161933,0.3163907,0.3165876,0.3167841,0.3169799,0.3171753,0.3173702,0.3175645,0.3177584,0.3179517,0.3181446,0.318337,0.3185288,0.3187202,0.3189111,0.3191015,0.3192914,0.3194808,0.3196698,0.3198583,0.3200463,0.3202338,0.3204209,0.3206075,0.3207936,0.3209793,0.3211645,0.3213492,0.3215335,0.3217173,0.3219007,0.3220836,0.3222661,0.3224481,0.3226297,0.3228109,0.3229916,0.3231719,0.3233517,0.3235312,0.3237101,0.3238887,0.3240668,0.3242445,0.3244218,0.3245986,0.324775,0.3249511,0.3251267,0.3253019,0.3254766,0.325651,0.3258249,0.3259985,0.3261716,0.3263444,0.3265167,0.3266887,0.3268602,0.3270314,0.3272021,0.3273725,0.3275425,0.3277121,0.3278813,0.3280501,0.3282186,0.3283866,0.3285543,0.3287216,0.3288885,0.3290551,0.3292213,0.3293871,0.3295525,0.3297176,0.3298823,0.3300466,0.3302106,0.3303742,0.3305375,0.3307004,0.3308629,0.3310251,0.3311869,0.3313484,0.3315095,0.3316703,0.3318307,0.3319908,0.3321506,0.33231,0.332469,0.3326277,0.3327861,0.3329442,0.3331018,0.3332592,0.3334162,0.3335729,0.3337293,0.3338853,0.3340411,0.3341964,0.3343515,0.3345062,0.3346606,0.3348147,0.3349685,0.335122,0.3352751,0.3354279,0.3355804,0.3357326,0.3358845,0.3360361,0.3361873,0.3363383,0.3364889,0.3366392,0.3367893,0.336939,0.3370884,0.3372375,0.3373863,0.3375349,0.3376831,0.337831,0.3379787,0.338126,0.338273,0.3384198,0.3385662,0.3387124,0.3388583,0.3390039,0.3391492,0.3392942,0.339439,0.3395834,0.3397276,0.3398715,0.3400151,0.3401584,0.3403015,0.3404443,0.3405868,0.340729,0.340871,0.3410127,0.3411541,0.3412952,0.3414361,0.3415767,0.341717};

//Reverb specific
float reverb_roomsize = 0.9;
float reverb_damping  = 0.999;

void setup() {
  //Configure SGT15000 audio chip
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(master_volume);
  sgtl5000_1.audioPostProcessorEnable();
  sgtl5000_1.adcHighPassFilterDisable();
  sgtl5000_1.eqSelect(3);//5-band eq
  sgtl5000_1.eqBands(eq_1, eq_2, eq_3, eq_4, eq_5);

  //Congfigure Teensy Audio Library
  AudioMemory(400);

  //Configure Audio Objects
  AudioNoInterrupts();

  //Frequency/Pitchbend Generation
  //  Oscillators are modulated with -1 to 1 representing a +/- 5 octaves at 0.2V per octave
  //  Everything starts at A=440, 0V
  //  
  //  Keyed_frequency_multiplier will be set from A-440 with (semitones_from_a440 * SEMITONE)
  //
  //  Two pitchbends, one for actual bends, one to be used with vibrato 
  cv_keyed_frequency_multiplier.amplitude(0);
  cv_pitchbend1_amount.amplitude(0);
  cv_pitchbend1_range.amplitude(2.0 * SEMITONE); //Two semitone range on normal bends 
  cv_pitchbend2_amount.amplitude(0);
  cv_pitchbend2_range.amplitude(1.0 * SEMITONE); // half semitone range for vibrato use
  pitch_mixer.gain(0, 1);
  pitch_mixer.gain(1, 1);
  pitch_mixer.gain(2, 1);
  oscillator1_pitch_mixer.gain(0, 1);
  oscillator1_pitch_mixer.gain(1, 1);
  oscillator1_pitch_mixer.gain(2, 1);
  oscillator2_pitch_mixer.gain(0, 1);
  oscillator2_pitch_mixer.gain(1, 1);
  oscillator2_pitch_mixer.gain(2, 1);
  oscillator3_pitch_mixer.gain(0, 1);
  oscillator3_pitch_mixer.gain(1, 1);
  oscillator3_pitch_mixer.gain(2, 1);
  oscillator4_pitch_mixer.gain(0, 1);
  oscillator4_pitch_mixer.gain(1, 1);
  oscillator4_pitch_mixer.gain(2, 1);
  oscillator5_pitch_mixer.gain(0, 1);
  oscillator5_pitch_mixer.gain(1, 1);
  oscillator5_pitch_mixer.gain(2, 1);
  cv_oscillator2_detune.amplitude(0);
  cv_oscillator3_detune.amplitude(0);
  cv_oscillator4_detune.amplitude(0);
  cv_oscillator5_detune.amplitude(0);
  cv_oscillator1_gain.amplitude(0);
  cv_oscillator2_gain.amplitude(0);
  cv_oscillator3_gain.amplitude(0);
  cv_oscillator4_gain.amplitude(0);
  cv_oscillator5_gain.amplitude(0);
  oscillator1_shape_mixer.gain(0, 1);
  oscillator1_shape_mixer.gain(1, 1);
  oscillator1_shape_mixer.gain(2, 1);
  oscillator2_shape_mixer.gain(0, 1);
  oscillator2_shape_mixer.gain(1, 1);
  oscillator2_shape_mixer.gain(2, 1);
  oscillator3_shape_mixer.gain(0, 1);
  oscillator3_shape_mixer.gain(1, 1);
  oscillator3_shape_mixer.gain(2, 1);
  oscillator4_shape_mixer.gain(0, 1);
  oscillator4_shape_mixer.gain(1, 1);
  oscillator4_shape_mixer.gain(2, 1);
  oscillator5_shape_mixer.gain(0, 1);
  oscillator5_shape_mixer.gain(1, 1);
  oscillator5_shape_mixer.gain(2, 1);
  cv_oscillator1_shape_modulation.amplitude(0);
  cv_oscillator2_shape_modulation.amplitude(0);
  cv_oscillator3_shape_modulation.amplitude(0);
  cv_oscillator4_shape_modulation.amplitude(0);
  cv_oscillator5_shape_modulation.amplitude(0);
  oscillator1.begin(1, oscillator_frequency, WAVEFORM_SAWTOOTH);
  oscillator1.frequencyModulation(oscillator_octaves);
  oscillator2.begin(1, oscillator_frequency, WAVEFORM_SAWTOOTH);
  oscillator2.frequencyModulation(oscillator_octaves);
  oscillator3.begin(1, oscillator_frequency, WAVEFORM_SAWTOOTH);
  oscillator3.frequencyModulation(oscillator_octaves);
  oscillator4.begin(1, oscillator_frequency, WAVEFORM_SAWTOOTH);
  oscillator4.frequencyModulation(oscillator_octaves);
  oscillator5.begin(1, oscillator_frequency, WAVEFORM_SAWTOOTH);
  oscillator5.frequencyModulation(oscillator_octaves);
  oscillator_mixer.gain(0, 1);
  oscillator_mixer.gain(1, 1);
  cv_white_noise_gain.amplitude(0);
  cv_pink_noise_gain.amplitude(0);
  pre_filter_mixer.gain(0, 1);
  pre_filter_mixer.gain(1, 1);
  pre_filter_mixer.gain(2, 1);
  pre_filter_mixer.gain(3, 1);
  filter.frequency(filter_frequency);
  filter.resonance(filter_resonance);
  filter.octaveControl(filter_octaves);
  pre_vca_mixer.gain(0, 1);//low pass
  pre_vca_mixer.gain(1, 0);//band pass
  pre_vca_mixer.gain(2, 0);//high pass
  pre_vca_mixer.gain(3, 0);//bypass
  pre_flange_mixer.gain(0, 1);//VCA
  pre_flange_mixer.gain(1, 0);//VCA Bypass (with filter)
  pre_flange_mixer.gain(2, 0);//Pre-Filter
  pre_flange_mixer.gain(3, 0);//input (SD player / Input)
  flange1.begin(delayline,FLANGE_DELAY_LENGTH,s_idx,s_depth,s_freq);
  pre_chorus_mixer.gain(0, 1);//flange bypass
  pre_chorus_mixer.gain(1, 0);//flange
  chorus1.begin(chorus_delayline,CHORUS_DELAY_LENGTH,n_chorus);
  pre_waveshape_mixer.gain(0, 1);//chorus bypass
  pre_waveshape_mixer.gain(1, 0);//chorus
  waveshape1.shape((float *)wave_shape_tube_12ax7_1025, 1025);
  pre_delay_mixer.gain(0, 1); //bypass waveshape
  pre_delay_mixer.gain(1, 0); //waveshape
  delay_mixer1.gain(0, 1); //Bypass
  delay_mixer1.gain(1, 1); //Delay 1-4
  delay_mixer1.gain(2, 1); //Delay 5-8
  delay1.delay(0, 50);  delay_mixer2.gain(0, 0);
  delay1.delay(1, 100); delay_mixer2.gain(1, 0);
  delay1.delay(2, 150); delay_mixer2.gain(2, 0);
  delay1.delay(3, 200); delay_mixer2.gain(3, 0);
  delay1.delay(4, 250); delay_mixer3.gain(0, 0);
  delay1.delay(5, 300); delay_mixer3.gain(1, 0);
  delay1.delay(6, 350); delay_mixer3.gain(2, 0);
  delay1.delay(7, 400); delay_mixer3.gain(3, 0);
  reverb.roomsize(reverb_roomsize);
  reverb.damping(reverb_damping);
  left.gain(0, 0.85); //dry
  left.gain(1, 0.15); //wet reverb
  left.gain(2, 0);    //input
  left.gain(3, 0);    //sd
  right.gain(0, 0.85);//dry
  right.gain(1, 0.15); //wet reverb
  right.gain(2, 0);    //input
  right.gain(3, 0);    //sd

  //LFOs
  cv_lfo1_frequency.amplitude(0);
  cv_lfo1_shape.amplitude(0);
  cv_lfo1_jitter_amount.amplitude(0);
  cv_lfo2_jitter_amount.amplitude(0);
  cv_lfo2_frequency.amplitude(0);
  cv_lfo2_shape.amplitude(0);
  lfo1.begin(1.0, oscillator_frequency, WAVEFORM_SINE);
  lfo1.frequencyModulation(oscillator_octaves);
  lfo2.begin(1.0, oscillator_frequency, WAVEFORM_SINE);
  lfo2.frequencyModulation(oscillator_octaves);
  lfo1_mixer.gain(0, 1);
  lfo1_mixer.gain(1, 1);
  lfo2_mixer.gain(0, 1);
  lfo2_mixer.gain(1, 1);
  cv_lfo_to_osc1_pitch_range.amplitude(0.1);//1 octave
  cv_lfo1_to_osc1_pitch_amount.amplitude(0);
  cv_lfo2_to_osc1_pitch_amount.amplitude(0);
  cv_oscillator1_shape_modulation.amplitude(0);
  cv_lfo_to_osc1_shape_range.amplitude(1);
  cv_lfo1_to_osc1_shape_amount.amplitude(0);
  cv_lfo2_to_osc1_shape_amount.amplitude(0);
  cv_lfo_to_osc2345_pitch_range.amplitude(0.1);//1 octave
  cv_lfo1_to_osc2345_pitch_amount.amplitude(0);
  cv_lfo2_to_osc2345_pitch_amount.amplitude(0);
  cv_lfo_to_osc2345_shape_range.amplitude(1);
  cv_lfo1_to_osc2345_shape_amount.amplitude(0);
  cv_lfo2_to_osc2345_shape_amount.amplitude(0);
  cv_1v.amplitude(1);
  cv_lfo1_to_vca_amount.amplitude(0);
  cv_lfo2_to_vca_amount.amplitude(0);
  lfo_to_vca_mixer.gain(0, 1);
  lfo_to_vca_mixer.gain(1, 1);
  lfo_to_vca_mixer.gain(2, 1);
  cv_vca_modulation.amplitude(0);
  cv_lfo1_to_filter_amount.amplitude(0);
  cv_lfo2_to_filter_amount.amplitude(0);
  lfo_to_filter_mixer1.gain(0, 1);
  lfo_to_filter_mixer1.gain(1, 1);
  lfo_to_filter_mixer1.gain(2, 1);
  cv_filter_frequency_amount.amplitude(0);
  cv_filter_frequency_offset.amplitude(1);
  lfo_to_filter_mixer2.gain(0, 1);
  lfo_to_filter_mixer2.gain(1, 1);

  //Inputs
  input_mixer.gain(0, 0); //In Left
  input_mixer.gain(1, 0); //In Right
  input_mixer.gain(2, 0); //SD Left
  input_mixer.gain(3, 0); //SD Right

  AudioInterrupts();
  
}

void loop() {}

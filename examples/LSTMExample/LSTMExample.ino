/**
 * Run a TensorFlow model to predict the IRIS dataset
 * For a complete guide, visit
 * https://eloquentarduino.com/tensorflow-lite-esp32
 */
// replace with your own model
// include BEFORE <eloquent_tinyml.h>!
#include <Arduino.h>
#include "model.h"
// include the runtime specific for your board
// either tflm_esp32 or tflm_cortexm
#include <tflm_esp32.h>
// now you can include the eloquent tinyml wrapper
#include <eloquent_tinyml.h>


// this is trial-and-error process
// when developing a new model, start with a high value
// (e.g. 10000), then decrease until the model stops
// working as expected
#define ARENA_SIZE 30000

Eloquent::TF::Sequential<TF_NUM_OPS, ARENA_SIZE> tf;

// sample data
float idle[450] = { -0.3334, 0.0289, -0.0031, -0.3315, 0.0305, -0.0030, -0.3325, 0.0292, -0.0023, -0.3364, 0.0265, -0.0017, -0.3391, 0.0242, -0.0012, -0.3380, 0.0229, -0.0010, -0.3367, 0.0209, -0.0012, -0.3370, 0.0206, -0.0013, -0.3369, 0.0231, -0.0012, -0.3369, 0.0261, -0.0012, -0.3359, 0.0292, -0.0018, -0.3344, 0.0300, -0.0025, -0.3338, 0.0286, -0.0026, -0.3341, 0.0278, -0.0026, -0.3351, 0.0276, -0.0026, -0.3359, 0.0279, -0.0026, -0.3367, 0.0265, -0.0026, -0.3373, 0.0248, -0.0028, -0.3369, 0.0253, -0.0026, -0.3357, 0.0266, -0.0023, -0.3344, 0.0286, -0.0023, -0.3338, 0.0281, -0.0026, -0.3341, 0.0253, -0.0028, -0.3341, 0.0253, -0.0026, -0.3349, 0.0266, -0.0022, -0.3357, 0.0279, -0.0022, -0.3354, 0.0292, -0.0022, -0.3346, 0.0300, -0.0022, -0.3339, 0.0289, -0.0022, -0.3343, 0.0266, -0.0025, -0.3341, 0.0266, -0.0026, -0.3338, 0.0283, -0.0026, -0.3349, 0.0296, -0.0026, -0.3367, 0.0300, -0.0025, -0.3373, 0.0296, -0.0022, -0.3365, 0.0261, -0.0018, -0.3354, 0.0222, -0.0015, -0.3356, 0.0201, -0.0009, -0.3364, 0.0200, -0.0005, -0.3375, 0.0204, -0.0004, -0.3385, 0.0217, -0.0000, -0.3377, 0.0245, -0.0002, -0.3367, 0.0268, -0.0007, -0.3360, 0.0283, -0.0012, -0.3357, 0.0292, -0.0020, -0.3356, 0.0297, -0.0030, -0.3356, 0.0297, -0.0038, -0.3349, 0.0296, -0.0038, -0.3344, 0.0291, -0.0035, -0.3346, 0.0284, -0.0028, -0.3349, 0.0281, -0.0025, -0.3351, 0.0278, -0.0022, -0.3343, 0.0274, -0.0020, -0.3331, 0.0281, -0.0020, -0.3336, 0.0292, -0.0018, -0.3352, 0.0279, -0.0022, -0.3370, 0.0232, -0.0023, -0.3373, 0.0204, -0.0018, -0.3369, 0.0222, -0.0017, -0.3369, 0.0245, -0.0017, -0.3367, 0.0274, -0.0018, -0.3346, 0.0294, -0.0017, -0.3326, 0.0292, -0.0017, -0.3336, 0.0279, -0.0023, -0.3339, 0.0281, -0.0030, -0.3338, 0.0292, -0.0033, -0.3347, 0.0292, -0.0031, -0.3357, 0.0289, -0.0026, -0.3360, 0.0274, -0.0025, -0.3352, 0.0245, -0.0025, -0.3341, 0.0229, -0.0026, -0.3341, 0.0227, -0.0025, -0.3360, 0.0216, -0.0018, -0.3385, 0.0200, -0.0012, -0.3391, 0.0208, -0.0012, -0.3382, 0.0234, -0.0015, -0.3377, 0.0255, -0.0020, -0.3364, 0.0274, -0.0025, -0.3341, 0.0300, -0.0028, -0.3331, 0.0310, -0.0035, -0.3341, 0.0286, -0.0038, -0.3347, 0.0263, -0.0033, -0.3354, 0.0263, -0.0030, -0.3367, 0.0266, -0.0028, -0.3380, 0.0252, -0.0025, -0.3377, 0.0240, -0.0022, -0.3352, 0.0250, -0.0022, -0.3339, 0.0261, -0.0022, -0.3341, 0.0265, -0.0022, -0.3352, 0.0247, -0.0018, -0.3367, 0.0226, -0.0013, -0.3369, 0.0229, -0.0015, -0.3351, 0.0248, -0.0023, -0.3331, 0.0271, -0.0030, -0.3326, 0.0283, -0.0033, -0.3346, 0.0273, -0.0031, -0.3362, 0.0268, -0.0025, -0.3364, 0.0276, -0.0022, -0.3362, 0.0270, -0.0023, -0.3360, 0.0232, -0.0022, -0.3370, 0.0206, -0.0020, -0.3380, 0.0214, -0.0018, -0.3383, 0.0227, -0.0022, -0.3369, 0.0242, -0.0026, -0.3356, 0.0247, -0.0026, -0.3347, 0.0253, -0.0025, -0.3343, 0.0273, -0.0023, -0.3341, 0.0283, -0.0025, -0.3344, 0.0273, -0.0026, -0.3351, 0.0253, -0.0028, -0.3359, 0.0245, -0.0028, -0.3365, 0.0255, -0.0031, -0.3362, 0.0266, -0.0035, -0.3356, 0.0258, -0.0038, -0.3352, 0.0245, -0.0036, -0.3354, 0.0255, -0.0030, -0.3360, 0.0274, -0.0026, -0.3360, 0.0261, -0.0028, -0.3360, 0.0221, -0.0028, -0.3388, 0.0224, -0.0033, -0.3380, 0.0250, -0.0031, -0.3356, 0.0263, -0.0026, -0.3351, 0.0278, -0.0031, -0.3339, 0.0283, -0.0036, -0.3333, 0.0286, -0.0038, -0.3333, 0.0289, -0.0036, -0.3343, 0.0283, -0.0033, -0.3354, 0.0245, -0.0035, -0.3359, 0.0195, -0.0040, -0.3354, 0.0206, -0.0043, -0.3352, 0.0250, -0.0048, -0.3367, 0.0270, -0.0051, -0.3367, 0.0273, -0.0051, -0.3352, 0.0266, -0.0046, -0.3341, 0.0274, -0.0043, -0.3338, 0.0276, -0.0040, -0.3346, 0.0263, -0.0035, -0.3359, 0.0255, -0.0031, -0.3369, 0.0244, -0.0030, -0.3367, 0.0231, -0.0031, -0.3354, 0.0234, -0.0036, -0.3346, 0.0253, -0.0041, -0.3349, 0.0265, -0.0046, -0.3349, 0.0255, -0.0048, -0.3343, 0.0250, -0.0046, -0.3344, 0.0253, -0.0041, -0.3352, 0.0245, -0.0035, -0.3360, 0.0237, -0.0030, -0.3369, 0.0239, -0.0028, -0.3375, 0.0232, -0.0030 };
float horizontal[450] = { -0.4638, -0.3242, 0.1993, -0.4544, -0.3369, 0.1930, -0.4449, -0.3400, 0.1868, -0.4365, -0.3304, 0.1834, -0.4184, -0.3171, 0.1814, -0.3985, -0.3026, 0.1785, -0.3805, -0.2873, 0.1752, -0.3640, -0.2648, 0.1724, -0.3491, -0.2404, 0.1692, -0.3316, -0.2199, 0.1666, -0.3177, -0.1992, 0.1651, -0.3100, -0.1804, 0.1648, -0.3048, -0.1615, 0.1638, -0.3027, -0.1390, 0.1619, -0.3009, -0.1154, 0.1606, -0.2970, -0.0912, 0.1593, -0.2918, -0.0669, 0.1570, -0.2867, -0.0453, 0.1544, -0.2838, -0.0235, 0.1519, -0.2810, -0.0008, 0.1490, -0.2768, 0.0231, 0.1451, -0.2693, 0.0532, 0.1405, -0.2597, 0.0860, 0.1357, -0.2499, 0.1197, 0.1296, -0.2412, 0.1575, 0.1230, -0.2325, 0.1974, 0.1171, -0.2221, 0.2353, 0.1113, -0.2110, 0.2726, 0.1036, -0.2003, 0.3167, 0.0933, -0.1889, 0.3660, 0.0820, -0.1743, 0.4132, 0.0701, -0.1583, 0.4562, 0.0584, -0.1469, 0.4936, 0.0473, -0.1437, 0.5221, 0.0382, -0.1388, 0.5398, 0.0282, -0.1315, 0.5452, 0.0172, -0.1306, 0.5427, 0.0094, -0.1319, 0.5364, 0.0063, -0.1298, 0.5300, 0.0076, -0.1284, 0.5229, 0.0110, -0.1318, 0.5084, 0.0141, -0.1388, 0.4863, 0.0164, -0.1494, 0.4576, 0.0188, -0.1637, 0.4208, 0.0232, -0.1804, 0.3803, 0.0297, -0.1988, 0.3447, 0.0387, -0.2182, 0.3188, 0.0496, -0.2366, 0.2981, 0.0616, -0.2517, 0.2704, 0.0754, -0.2670, 0.2327, 0.0881, -0.2820, 0.1938, 0.0997, -0.2888, 0.1619, 0.1108, -0.2838, 0.1420, 0.1220, -0.2727, 0.1396, 0.1275, -0.2856, 0.1498, 0.1311, -0.3346, 0.1396, 0.1515, -0.3696, 0.0859, 0.1685, -0.3649, 0.0104, 0.1632, -0.3456, -0.0480, 0.1549, -0.3302, -0.0713, 0.1513, -0.3160, -0.0786, 0.1497, -0.3066, -0.0956, 0.1508, -0.3136, -0.1258, 0.1554, -0.3320, -0.1602, 0.1630, -0.3587, -0.1945, 0.1724, -0.3748, -0.2282, 0.1803, -0.3749, -0.2591, 0.1861, -0.3787, -0.2829, 0.1900, -0.3878, -0.2956, 0.1952, -0.3994, -0.3018, 0.2016, -0.4086, -0.3062, 0.2066, -0.4184, -0.3125, 0.2100, -0.4256, -0.3127, 0.2107, -0.4282, -0.3039, 0.2083, -0.4291, -0.2881, 0.2045, -0.4319, -0.2676, 0.2024, -0.4357, -0.2408, 0.2035, -0.4340, -0.2051, 0.2070, -0.4311, -0.1664, 0.2125, -0.4282, -0.1276, 0.2175, -0.4231, -0.0936, 0.2201, -0.4122, -0.0642, 0.2192, -0.3948, -0.0324, 0.2138, -0.3740, 0.0058, 0.2039, -0.3517, 0.0463, 0.1915, -0.3334, 0.0877, 0.1790, -0.3160, 0.1284, 0.1674, -0.2978, 0.1625, 0.1555, -0.2791, 0.1959, 0.1427, -0.2568, 0.2338, 0.1288, -0.2324, 0.2748, 0.1150, -0.2099, 0.3170, 0.1003, -0.1883, 0.3598, 0.0820, -0.1660, 0.3972, 0.0588, -0.1437, 0.4207, 0.0338, -0.1259, 0.4353, 0.0097, -0.1179, 0.4389, -0.0113, -0.1153, 0.4332, -0.0264, -0.1126, 0.4275, -0.0362, -0.1114, 0.4215, -0.0424, -0.1126, 0.4127, -0.0455, -0.1160, 0.4011, -0.0455, -0.1243, 0.3933, -0.0414, -0.1355, 0.3909, -0.0344, -0.1404, 0.3953, -0.0272, -0.1398, 0.4049, -0.0210, -0.1409, 0.4163, -0.0147, -0.1456, 0.4221, -0.0082, -0.1494, 0.4177, -0.0026, -0.1497, 0.4081, 0.0027, -0.1495, 0.3969, 0.0089, -0.1495, 0.3829, 0.0173, -0.1497, 0.3701, 0.0291, -0.1521, 0.3578, 0.0431, -0.1640, 0.3354, 0.0582, -0.1842, 0.3028, 0.0732, -0.2057, 0.2636, 0.0870, -0.2249, 0.2184, 0.1005, -0.2389, 0.1731, 0.1143, -0.2514, 0.1341, 0.1298, -0.2659, 0.1000, 0.1466, -0.2812, 0.0694, 0.1617, -0.2949, 0.0499, 0.1739, -0.3069, 0.0370, 0.1851, -0.3276, 0.0091, 0.1951, -0.3518, -0.0334, 0.2047, -0.3743, -0.0752, 0.2135, -0.3945, -0.1122, 0.2169, -0.4134, -0.1405, 0.2187, -0.4300, -0.1608, 0.2206, -0.4391, -0.1753, 0.2232, -0.4508, -0.1911, 0.2242, -0.4663, -0.2082, 0.2247, -0.4773, -0.2233, 0.2281, -0.4820, -0.2411, 0.2299, -0.4861, -0.2600, 0.2275, -0.4900, -0.2774, 0.2226, -0.4881, -0.2923, 0.2179, -0.4786, -0.3031, 0.2130, -0.4669, -0.3033, 0.2073, -0.4536, -0.2958, 0.2011, -0.4347, -0.2819, 0.1944, -0.4116, -0.2609, 0.1879, -0.3881, -0.2359, 0.1824, -0.3642, -0.2053, 0.1785, -0.3430, -0.1729, 0.1754, -0.3240, -0.1437, 0.1720, -0.3069, -0.1166, 0.1684, -0.2932, -0.0936, 0.1646, -0.2838, -0.0734, 0.1594 };
float vertical[450] = { -0.5387, 0.1786, 0.0916, -0.6150, 0.1673, 0.1033, -0.6876, 0.1510, 0.1156, -0.7535, 0.1344, 0.1272, -0.8173, 0.1166, 0.1376, -0.8772, 0.0886, 0.1458, -0.9124, 0.0748, 0.1488, -0.9212, 0.0701, 0.1516, -0.9368, 0.0598, 0.1555, -0.9498, 0.0567, 0.1589, -0.9444, 0.0623, 0.1628, -0.9234, 0.0755, 0.1651, -0.8875, 0.0867, 0.1645, -0.8354, 0.0981, 0.1593, -0.7742, 0.1139, 0.1524, -0.7153, 0.1261, 0.1451, -0.6629, 0.1306, 0.1357, -0.6201, 0.1287, 0.1262, -0.5838, 0.1199, 0.1186, -0.5484, 0.1049, 0.1126, -0.5148, 0.0891, 0.1059, -0.4842, 0.0732, 0.0982, -0.4523, 0.0602, 0.0906, -0.4160, 0.0470, 0.0846, -0.3714, 0.0359, 0.0787, -0.3193, 0.0344, 0.0704, -0.2670, 0.0419, 0.0595, -0.2161, 0.0528, 0.0468, -0.1691, 0.0566, 0.0343, -0.1319, 0.0634, 0.0196, -0.1031, 0.0729, 0.0051, -0.0756, 0.0769, -0.0046, -0.0471, 0.0795, -0.0131, -0.0229, 0.0769, -0.0232, -0.0050, 0.0676, -0.0328, 0.0113, 0.0502, -0.0393, 0.0241, 0.0323, -0.0450, 0.0350, 0.0167, -0.0502, 0.0449, 0.0017, -0.0531, 0.0495, -0.0103, -0.0533, 0.0503, -0.0170, -0.0510, 0.0480, -0.0150, -0.0459, 0.0415, -0.0069, -0.0383, 0.0336, -0.0000, -0.0297, 0.0239, -0.0015, -0.0227, 0.0093, -0.0100, -0.0176, -0.0042, -0.0191, -0.0131, -0.0126, -0.0238, -0.0085, -0.0232, -0.0262, -0.0036, -0.0382, -0.0292, 0.0030, -0.0543, -0.0339, 0.0102, -0.0696, -0.0389, 0.0157, -0.0821, -0.0402, 0.0195, -0.0934, -0.0350, 0.0227, -0.1052, -0.0213, 0.0269, -0.1181, -0.0004, 0.0323, -0.1284, 0.0265, 0.0388, -0.1409, 0.0527, 0.0439, -0.1650, 0.0753, 0.0474, -0.2068, 0.0960, 0.0527, -0.2262, 0.0961, 0.0626, -0.2644, 0.1108, 0.0652, -0.3168, 0.1314, 0.0655, -0.3609, 0.1349, 0.0725, -0.4247, 0.1401, 0.0798, -0.4861, 0.1352, 0.0906, -0.5576, 0.1238, 0.1015, -0.6331, 0.1087, 0.1130, -0.7120, 0.0956, 0.1238, -0.7760, 0.0789, 0.1339, -0.8230, 0.0663, 0.1433, -0.8611, 0.0605, 0.1492, -0.8878, 0.0572, 0.1541, -0.8979, 0.0657, 0.1581, -0.8951, 0.0660, 0.1625, -0.9029, 0.0541, 0.1664, -0.9016, 0.0491, 0.1681, -0.8821, 0.0468, 0.1687, -0.8590, 0.0460, 0.1684, -0.8225, 0.0484, 0.1679, -0.7770, 0.0496, 0.1661, -0.7317, 0.0497, 0.1620, -0.6878, 0.0512, 0.1558, -0.6427, 0.0540, 0.1487, -0.5974, 0.0593, 0.1422, -0.5530, 0.0620, 0.1349, -0.5082, 0.0621, 0.1262, -0.4636, 0.0628, 0.1166, -0.4213, 0.0610, 0.1078, -0.3829, 0.0605, 0.0995, -0.3354, 0.0519, 0.0922, -0.2830, 0.0397, 0.0847, -0.2394, 0.0359, 0.0753, -0.2031, 0.0305, 0.0640, -0.1695, 0.0182, 0.0502, -0.1326, 0.0151, 0.0346, -0.0869, 0.0187, 0.0193, -0.0414, 0.0118, 0.0032, -0.0086, 0.0008, -0.0140, 0.0173, -0.0101, -0.0292, 0.0430, -0.0155, -0.0419, 0.0718, -0.0157, -0.0529, 0.1011, -0.0212, -0.0606, 0.1244, -0.0340, -0.0640, 0.1384, -0.0515, -0.0669, 0.1376, -0.0744, -0.0681, 0.1195, -0.0939, -0.0651, 0.0902, -0.1005, -0.0578, 0.0500, -0.0918, -0.0461, 0.0111, -0.0723, -0.0316, -0.0156, -0.0448, -0.0175, -0.0364, -0.0122, -0.0053, -0.0527, 0.0161, 0.0053, -0.0613, 0.0340, 0.0141, -0.0652, 0.0460, 0.0199, -0.0694, 0.0528, 0.0224, -0.0753, 0.0556, 0.0225, -0.0831, 0.0603, 0.0245, -0.1023, 0.0712, 0.0308, -0.1368, 0.0859, 0.0385, -0.1712, 0.0939, 0.0440, -0.1962, 0.0973, 0.0455, -0.2088, 0.0838, 0.0504, -0.2324, 0.0872, 0.0496, -0.2542, 0.0870, 0.0445, -0.2685, 0.0703, 0.0445, -0.2901, 0.0621, 0.0431, -0.2968, 0.0410, 0.0471, -0.3167, 0.0255, 0.0585, -0.3644, 0.0222, 0.0745, -0.4148, 0.0437, 0.0717, -0.4622, 0.0803, 0.0273, -0.5445, 0.0794, -0.0079, -0.6842, 0.0440, 0.0237, -0.8333, 0.0216, 0.0992, -0.9581, 0.0257, 0.1858, -1.0000, 0.0738, 0.2670, -1.0000, 0.1581, 0.3233, -1.0000, 0.2535, 0.3445, -1.0000, 0.3333, 0.3417, -1.0000, 0.3915, 0.3193, -0.9859, 0.4314, 0.2779, -0.8331, 0.4270, 0.2291, -0.6754, 0.3801, 0.1840, -0.5463, 0.3095, 0.1471, -0.4643, 0.2306, 0.1114, -0.4247, 0.1570, 0.0831, -0.4067, 0.0976, 0.0701, -0.3966, 0.0496, 0.0642, -0.3878, 0.0152, 0.0600 };

/**
 * Run prediction
 */
void predictSample(const char *classLabel, float *input, uint8_t expectedOutput) {
    // classify class 0
    if (!tf.predict(input).isOk()) {
        Serial.println(tf.exception.toString());
        return;
    }

    Serial.print("Predicting sample of ");
    Serial.print(classLabel);
    Serial.print(": expcted id=");
    Serial.print(expectedOutput);
    Serial.print(", predicted=");
    Serial.println(tf.classification);
}

/**
 *
 */
void setup() {
    Serial.begin(115200);
    delay(3000);
    Serial.println("__TENSORFLOW LSTM__");

    // configure input/output
    // (not mandatory if you generated the .h model
    // using the eloquent_tensorflow Python package)
    tf.setNumInputs(TF_NUM_INPUTS);
    tf.setNumOutputs(TF_NUM_OUTPUTS);

    registerNetworkOps(tf);

    while (!tf.begin(tfModel).isOk()) {
        Serial.println(tf.exception.toString());
        delay(1000);
    }
}


void loop() {
    predictSample("idle", idle, 0);
    predictSample("horizontal", horizontal, 1);
    predictSample("vertical", vertical, 2);

    // how long does it take to run a single prediction?
    Serial.print("It takes ");
    Serial.print(tf.benchmark.microseconds());
    Serial.println("us for a single prediction");

    delay(1000);
}
#include "config.h"

const char* DEVICE_ID = "OUTSEAL_1";

SensorNodeInfo sensorConfig[8] = {
  {7, "s_atas", "cwt"},
  {2, "s_bawah", "cwt"},
  {3, "wt_a", "npk"},
  {4, "sr_a", "cwt"},
  {5, "sr_b", "cwt"},
  {6, "wt_b", "npk"},
  {0, "wl1", "digital"},  
  {0, "wl2", "digital"}   // Digital sensor for WT2 on S2
};

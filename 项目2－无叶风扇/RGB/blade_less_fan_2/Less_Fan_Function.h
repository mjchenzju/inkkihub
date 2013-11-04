#include <Arduino.h>
#include <IRremote.h>

#define remote_up 16736925
#define remote_down 16754775 
#define remote_left 16720605
#define remote_right 16761405
#define enter_key 16712445
#define one_key 16738455 
#define two_key 16750695
#define three_key 16756815
#define four_key 16724175 
#define five_key 16718055
#define six_key 16743045
#define seven_key 16716015
#define eight_key 16726215 
#define nine_key 16734885
#define zero_key 16730805

class Less_Fan_Function
{
  public:
  Less_Fan_Function(void);
  int dump(decode_results *results);
};

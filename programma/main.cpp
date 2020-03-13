#include "rccregisters.hpp" //for RTC
#include "gpioaregisters.hpp" //for gpioa
#include "gpiocregisters.hpp" //for gpioc
#include "tim2registers.hpp" //for tim2

extern "C"

{
  int __low_level_init(void) //nizcourovnevii log signal
  {
    RCC::CR::HSION::Enable::Set (); //vkluchaem vnutrennii genirator
    while ( ! RCC::CR::HSIRDY::Enable::IsSet () ) //zadergka dla yctranenia drebezga
    {
    };
    
      RCC::CFGR::SW::Hsi::Set(); //podkluchaem vntrennii genirator
      while ( ! RCC::CFGR::SWS::Hsi::IsSet () ) //zadergka dla yctranenia drebezga
    {
    };
    RCC::AHB1ENR::GPIOAEN::Enable::Set(); //podkluchaem k vntrennii genirator gpia
    GPIOA::MODER::MODER5::Output::Set(); //nastraivaem port on output
    
    RCC::AHB1ENR::GPIOCEN::Enable::Set(); //podkluchaem k vntrennii genirator gpia
    GPIOC::MODER::MODER5::Output::Set(); //nastraivaem port on output
    GPIOC::MODER::MODER8::Output::Set(); //nastraivaem port on output
    GPIOC::MODER::MODER9::Output::Set(); //nastraivaem port on output
    GPIOC::MODER::MODER13::Input::Set(); //nastraivaem port on input
    
    RCC::APB1ENR::TIM2EN::Enable::Set(); //podkluchaem k vntrennii genirator tim2
    TIM2::CR1::URS::Overflow::Set(); //ystanavlivaem prerivanie po perepolneniu
    return 0;
  }
}

void delay(std::uint32_t delay) //podprogramma zaderzki
{
  TIM2::ARR::Write(16'000 *delay);  //dlitelnost zaderzki
  TIM2::SR::UIF::NoUpdate::Set(); //cnatie flaga
  TIM2::CNT::Write(0); //ystanavlivaem chetchik in 0
  TIM2::CR1::CEN::Enable::Set(); //start
  while(TIM2::SR::UIF::NoUpdate::IsSet()) //ozidanie ystanivlenia flaga
   {
   }                       
};

 struct Button 
 {
   static bool IsPressed()
   {
     bool result = false;  //result = false
     if (GPIOC::IDR::IDR13::Low::IsSet() ) //if idr13 vkl
     {
       while (GPIOC::IDR::IDR13::Low::IsSet() ) //zaderzka dla vkluchenia
       {
         result = true; //result = true
       };
     }
     return result; //vivod result
   }
 };

template <typename Port, std::uint32_t pinNum>
struct Led
{
  static void Toggle()
  {
    Port::ODR::Toggle(1<<pinNum); //izmenaem znachenie nomera pin
  }
};

using Led1 = Led<GPIOC,5>; //vkl led1
using Led2 = Led<GPIOC,8>; //vkl led2
using Led3 = Led<GPIOC,9>; //vkl led3
using Led4 = Led<GPIOA,5>; //vkl led4

int main()
{
  for(;;)
  {
    Led1::Toggle();
    Led2::Toggle();
    Led3::Toggle();
    Led4::Toggle();
    Delay(500);
    Led1::Toggle();
    Led2::Toggle();
    Led3::Toggle();
    Led4::Toggle();
    Delay(500);
  }
  return 0;
}


int main()
{
  for(;;)
  {
    Led1::Toggle();
    Led2::Toggle();
    Led3::Toggle();
    Led4::Toggle();
    Delay(500);
    Led1::Toggle();
    Led2::Toggle();
    Led3::Toggle();
    Led4::Toggle();
    Delay(500);
    Led1::Toggle();
    Led2::Toggle();
    Led3::Toggle();
    Led4::Toggle();
    Delay(1'000);
    Led1::Toggle();
    Led2::Toggle();
    Led3::Toggle();
    Led4::Toggle();
    Delay(1'000);
    Led1::Toggle();
    Led2::Toggle();
    Led3::Toggle();
    Led4::Toggle();
    Delay(1'500);
    Led1::Toggle();
    Led2::Toggle();
    Led3::Toggle();
    Led4::Toggle();
    Delay(1'500);
  }
  return 0;
}

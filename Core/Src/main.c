#include "main.h"

TIM_HandleTypeDef htim2;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);

int main(void)
{
  HAL_Init();

  // Sistem saatini 168 MHz olarak yapılandır
  SystemClock_Config();

  // GPIO ve Timer donanımlarını başlat
  MX_GPIO_Init();
  MX_TIM2_Init();

  // Timer2'yi Interrupt (Kesme) moduyla başlat
  HAL_TIM_Base_Start_IT(&htim2);

  while (1)
  {
      // Ana döngü boş. Tüm işlemler Timer Kesmesi (Interrupt) ile yapılıyor.
      // Bu, işlemciyi (CPU) meşgul etmeyen en optimize yöntemdir.
  }
}

// Timer Kesme (Interrupt) Fonksiyonu
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM2)
  {
      // Timer her taştığında (belirlenen süre dolduğunda) GPIO pininin durumunu değiştir (Toggle)
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12); 
  }
}

static void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  
  // 168 MHz sistem saatine göre 1 saniyelik gecikme hesabı (Optimizasyon)
  htim2.Init.Prescaler = 16800 - 1; // Timer clock 10 kHz'e düşürüldü
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10000 - 1;    // 10 kHz saat ile 10.000 sayma = 1 Saniye
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim2);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // GPIO Port D'nin saatini aktif et
  __HAL_RCC_GPIOD_CLK_ENABLE();

  // PD12 pinini Çıkış (Output) olarak ayarla
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

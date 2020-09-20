#include "goldobot/platform/hal_private.hpp"
#include "goldobot/platform/hal_io_device.hpp"
#include "goldobot/platform/hal_gpio.hpp"
#include "goldobot/platform/hal_uart.hpp"

extern "C"
{
	#include "stm32f3xx_hal_i2c.h"
	#include "stm32f3xx_ll_gpio.h"
	#include "stm32f3xx_ll_bus.h"

    void goldobot_hal_i2c_ev_irq_handler(int ioc_index);
    void goldobot_hal_i2c_er_irq_handler(int ioc_index);
}

namespace goldobot { namespace platform {
	I2C_HandleTypeDef g_i2c_handles[3];
} }; // namespace goldobot::platform


void goldobot_hal_i2c_ev_irq_handler(int ioc_index)
{
	HAL_I2C_EV_IRQHandler(&goldobot::platform::g_i2c_handles[ioc_index]);
}

void goldobot_hal_i2c_er_irq_handler(int ioc_index)
{
	HAL_I2C_ER_IRQHandler(&goldobot::platform::g_i2c_handles[ioc_index]);
}


namespace goldobot { namespace platform {

void hal_i2c_init(IODevice* device, const IODeviceConfigI2c* config)
{
	int i2c_index = (int)config->device_id - (int)DeviceId::I2c1;

	IRQn_Type ev_irq_n;
	IRQn_Type er_irq_n;

	I2C_HandleTypeDef* i2c_handle = &g_i2c_handles[i2c_index];
	I2C_TypeDef* i2c_instance;

	switch(config->device_id)
	{
	case DeviceId::I2c1:
		i2c_instance = I2C1;
		ev_irq_n = I2C1_EV_IRQn;
		er_irq_n = I2C1_ER_IRQn;
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
		break;
	case DeviceId::I2c2:
		i2c_instance = I2C2;
		ev_irq_n = I2C2_EV_IRQn;
		er_irq_n = I2C2_ER_IRQn;
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
		break;
	case DeviceId::I2c3:
		i2c_instance = I2C3;
		ev_irq_n = I2C3_EV_IRQn;
		er_irq_n = I2C3_ER_IRQn;
		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C3);
		break;
	default:
		break;
	}



}


}}; // namespace goldobot::platform

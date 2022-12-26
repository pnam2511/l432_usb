#include "usbd_driver.h"

void initialize_usb_pins(void)
{
    /* Enable clock for GPIOA */
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN);

    /* Set alternate function for: PA11(-), PA12(+) */
    MODIFY_REG(GPIOA->AFR[1],
        GPIO_AFRH_AFSEL11 | GPIO_AFRH_AFSEL12,
        _VAL2FLD(GPIO_AFRH_AFSEL11, 0xA) | _VAL2FLD(GPIO_AFRH_AFSEL12, 0xA)
    );

    /* Configues USB pins to work in alternate funciton mode */
    MODIFY_REG(GPIOA->MODER,
        GPIO_MODER_MODER11 | GPIO_MODER_MODER12,
        _VAL2FLD(GPIO_MODER_MODER11, 2) | _VAL2FLD(GPIO_MODER_MODER12, 2)
    );
}

void initialize_core(void)
{
    /* Enables clock for USB core */
    SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USBFSEN);
    
    /* Supply voltage for USB transceiver */
    CLEAR_BIT(USB->CNTR, USB_CNTR_PDWN);

    /* Wait for t_startup time */
    HAL_DELAY(1);

    /* Remove reset condition */
    CLEAR_BIT(USB->CNTR, USB_CNTR_FRES);

    /* Unmasks main USB core interrupts */
    SET_BIT(USB->CNTR, USB_CNTR_RESETM | USB_CNTR_SOFM | USB_CNTR_SUSPM | USB_CNTR_WKUPM);

    /* Clear all pending core interrupts */
    CLEAR_BIT(USB->ISTR, USB_ISTR_PMAOVR | USB_ISTR_ERR | USB_ISTR_WKUP | USB_ISTR_SUSP | USB_ISTR_RESET | USB_ISTR_SOF | USB_ISTR_ESOF | USB_ISTR_L1REQ);


}
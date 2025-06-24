#include "lcd.h"
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(bme680_sample, LOG_LEVEL_INF);

void convert_into_string(uint8_t *str,int32_t val1,int32_t val2){
    val2/=10000;
    
    str[0]=(val1/10)+48;
    str[1]=(val1%10)+48;
   
    str[2]='.';
   
    str[3]=((val2/10)%10)+48;
    str[4]=((val2%10)%10)+48;
    str[5]=0;
    str[6]=0;
    str[7]='\0';
}


int main(void) {
 
    uint8_t str[10];
    const struct device *dev = DEVICE_DT_GET_ANY(bosch_bme680);

    const struct device *i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));
    
    if (!device_is_ready(i2c_dev)) {
        printk("I2C not ready!\n");
        return 0;
    }
    
    if (!dev) {
        LOG_ERR("BME680: Device not found.");
        return 0;
    }

    if (!device_is_ready(dev)) {
        LOG_ERR("BME680: Device is not ready.");
        return 0;
    }

    LOG_INF("BME680: Device is ready at %s", dev->name);

    lcd_init(i2c_dev);
    
    struct sensor_value temp, press, hum, gas_res;
    
    while(1){   
   
        
        if (sensor_sample_fetch(dev) < 0) {
            LOG_ERR("Failed to fetch sample");
            continue;
        }

        if (sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp) < 0) {
            LOG_ERR("Failed to get temperature");
            continue;
        }
        if (sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press) < 0) {
            LOG_ERR("Failed to get pressure");
            continue;
        }

        if (sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &hum) < 0) {
            LOG_ERR("Failed to get humidity");
            continue;
        }

        if (sensor_channel_get(dev, SENSOR_CHAN_GAS_RES, &gas_res) < 0) {
            LOG_WRN("Gas resistance not available (optional feature)");
            gas_res.val1 = 0;
            gas_res.val2 = 0;
        }

        LOG_INF("Temp: %d.%06d C", temp.val1, temp.val2);
        LOG_INF("Press: %d.%06d kPa", press.val1, press.val2);
        LOG_INF("Humidity: %d.%06d %%", hum.val1, hum.val2);
        LOG_INF("Gas Resistance: %d.%06d Ohms", gas_res.val1, gas_res.val2);
        
   //     lcd_init(i2c_dev);

        lcd_send_cmd(i2c_dev,0x80);
        lcd_print(i2c_dev,"GHANSHYAM PATIDAR");
    
        lcd_send_cmd(i2c_dev,0x94);

        convert_into_string(str,temp.val1,temp.val2);
        str[5]=0xdf;
        str[6]='C';

        lcd_print(i2c_dev,"Temp= ");
        lcd_print(i2c_dev,str);
        
        lcd_send_cmd(i2c_dev,0xd4);
        
        convert_into_string(str,press.val1,press.val2);
        str[5]='K';
        str[6]='p';
        lcd_print(i2c_dev,"Press= ");
        lcd_print(i2c_dev,str);
    
        // lcd_send_cmd(i2c_dev,0x01);
       // k_msleep(2); 
        
        k_sleep(K_SECONDS(2));
        
    }
    while(1);
}


import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import (
    CONF_ID,
    CONF_VOLTAGE,
)

DEPENDENCIES = ['uart']
MULTI_CONF = True

CONF_PHASE_A = "phase_a"

bl6552_ns = cg.esphome_ns.namespace('bl6552')
BL6552 = bl6552_ns.class_('BL6552', cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(BL6552),
    cv.Optional(CONF_PHASE_A): cv.Schema({
        cv.Optional(CONF_VOLTAGE): sensor.sensor_schema(),
    }),
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_PHASE_A in config:
        phase_a = config[CONF_PHASE_A]
        if CONF_VOLTAGE in phase_a:
            sens = await sensor.new_sensor(phase_a[CONF_VOLTAGE])
            cg.add(var.set_phase_a_voltage_sensor(sens))
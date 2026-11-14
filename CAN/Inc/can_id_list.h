/*
 * can_id_list.h
 *
 * AUTO-GENERATED FILE - DO NOT EDIT BY HAND.
 * Source: Eko-Energia/CAN-DATABASE/CAN_DB.dbc
 * Generator: scripts/gen_can_id_list.py (Eko-Energia/cantools fork)
 * Change the DBC instead; this file is regenerated on every merge.
 */

#ifndef INC_CAN_ID_LIST_H_
#define INC_CAN_ID_LIST_H_

#define PEDALS_STATIC_ENGINESNMT_FRAME_ID        (0x00u)        /* standard, sender: Pedals */
#define SAFESTATE_ACTIV_FRAME_ID                 (0x01u)        /* standard, sender: - */
#define SAFESTATE_ACCVAL_FRAME_ID                (0x02u)        /* standard, sender: SafeState */
#define SAFESTATE_NODE_FRAME_ID                  (0x03u)        /* standard, sender: SafeState */
#define COOLINGCABINMANUAL_FRAME_ID              (0x0du)        /* standard, sender: - */
#define SAFESTATE_SYNCTICK_FRAME_ID              (0x1eu)        /* standard, sender: SafeState */
#define SAFESTATE_END_FRAME_ID                   (0x1fu)        /* standard, sender: SafeState */
#define PEDALS_NODE_FRAME_ID                     (0x40u)        /* standard, sender: Pedals */
#define PEDALS_JTSN_WORKS_FRAME_ID               (0x41u)        /* standard, sender: Pedals */
#define PEDALS_END_FRAME_ID                      (0x5fu)        /* standard, sender: Pedals */
#define BMSMASTER_NODE_FRAME_ID                  (0x80u)        /* standard, sender: BMSMaster */
#define BMSMASTER_MASTERVOLTCURRTEMP_FRAME_ID    (0x82u)        /* standard, sender: BMSMaster */
#define BMSMASTER_PCBSTHERM1TEMP_FRAME_ID        (0x83u)        /* standard, sender: BMSMaster */
#define BMSMASTER_PCBSTHERM2TEMP_FRAME_ID        (0x84u)        /* standard, sender: BMSMaster */
#define BMSMASTER_PCBSTHERM3TEMP_FRAME_ID        (0x85u)        /* standard, sender: BMSMaster */
#define BMSMASTER_PCBSTHERM4TEMP_FRAME_ID        (0x86u)        /* standard, sender: BMSMaster */
#define BMSMASTER_PCBSTHERM5TEMP_FRAME_ID        (0x87u)        /* standard, sender: BMSMaster */
#define BMSMASTER_PCBSTHERM6TEMP_FRAME_ID        (0x88u)        /* standard, sender: BMSMaster */
#define BMSMASTER_PCBSTHERM7TEMP_FRAME_ID        (0x89u)        /* standard, sender: BMSMaster */
#define BMSMASTER_PCBSTHERM8TEMP_FRAME_ID        (0x8au)        /* standard, sender: BMSMaster */
#define BMSMASTER_PCBSTHERM9TEMP_FRAME_ID        (0x8bu)        /* standard, sender: BMSMaster */
#define BMSMASTER_JK_PACK_FRAME_ID               (0x8cu)        /* standard, sender: BMSMaster */
#define BMSMASTER_JK_CELLS_1_4_FRAME_ID          (0x8du)        /* standard, sender: BMSMaster */
#define BMSMASTER_JK_CELLS_5_8_FRAME_ID          (0x8eu)        /* standard, sender: BMSMaster */
#define BMSMASTER_JK_CELLS_9_12_FRAME_ID         (0x8fu)        /* standard, sender: BMSMaster */
#define BMSMASTER_JK_CELLS_13_16_FRAME_ID        (0x90u)        /* standard, sender: BMSMaster */
#define BMSMASTER_JK_CELLS_17_20_FRAME_ID        (0x91u)        /* standard, sender: BMSMaster */
#define BMSMASTER_JK_CELLS_21_FRAME_ID           (0x92u)        /* standard, sender: BMSMaster */
#define BMSMASTER_JK_TEMP_FRAME_ID               (0x93u)        /* standard, sender: BMSMaster */
#define BMSMASTER_JK_CYCLESTATS_FRAME_ID         (0x94u)        /* standard, sender: BMSMaster */
#define BMSMASTER_END_FRAME_ID                   (0x9fu)        /* standard, sender: BMSMaster */
#define ENGINELEFT_STATIC_EMCY_FRAME_ID          (0xa6u)        /* standard, sender: EngineLeft */
#define ENGINERIGHT_STATIC_EMCY_FRAME_ID         (0xa7u)        /* standard, sender: EngineRight */
#define RCD_STATIC_NODE_FRAME_ID                 (0xc0u)        /* standard, sender: RCD */
#define RCD_STATUS_FRAME_ID                      (0xc1u)        /* standard, sender: RCD */
#define RCD_STATIC_END_FRAME_ID                  (0xdfu)        /* standard, sender: RCD */
#define ENGINELEFT_STATIC_TPDO1_FRAME_ID         (0x1a6u)       /* standard, sender: EngineLeft */
#define ENGINERIGHT_STATIC_TPDO1_FRAME_ID        (0x1a7u)       /* standard, sender: EngineRight */
#define JETSON_STATIC_NODE_FRAME_ID              (0x200u)       /* standard, sender: JETSON */
#define JETSON_STATIC_CHILDMODE_FRAME_ID         (0x201u)       /* standard, sender: JETSON */
#define JETSON_STATIC_PEDALSENSITIVITY_FRAME_ID  (0x202u)       /* standard, sender: JETSON */
#define JETSON_STATIC_TORQUEVECTORING_FRAME_ID   (0x203u)       /* standard, sender: JETSON */
#define JETSON_STATIC_END_FRAME_ID               (0x21fu)       /* standard, sender: JETSON */
#define JETSON_STATIC_ENGINELEFT_RPDO1_FRAME_ID  (0x226u)       /* standard, sender: JETSON */
#define JETSON_STATIC_ENGINERIGHT_RPDO1_FRAME_ID (0x227u)       /* standard, sender: JETSON */
#define ENGINELEFT_STATIC_TPDO2_FRAME_ID         (0x2a6u)       /* standard, sender: EngineLeft */
#define ENGINERIGHT_STATIC_TPDO2_FRAME_ID        (0x2a7u)       /* standard, sender: EngineRight */
#define SMALLBMS_NODE_FRAME_ID                   (0x360u)       /* standard, sender: SmallBMS */
#define SMALLBMS_END_FRAME_ID                    (0x37fu)       /* standard, sender: SmallBMS */
#define DASHBOARD_NODE_FRAME_ID                  (0x3e0u)       /* standard, sender: Dashboard */
#define DASHBOARD_CONTROL_FRAME_ID               (0x3e1u)       /* standard, sender: Dashboard */
#define DASHBOARD_LIGHTS_FRAME_ID                (0x3e2u)       /* standard, sender: Dashboard */
#define DASHBOARD_WIPERS_FRAME_ID                (0x3e3u)       /* standard, sender: Dashboard */
#define DASHBOARD_CC_FRAME_ID                    (0x3e4u)       /* standard, sender: Dashboard */
#define DASHBOARD_END_FRAME_ID                   (0x3ffu)       /* standard, sender: Dashboard */
#define MPPT_NODE_FRAME_ID                       (0x460u)       /* standard, sender: MPPT */
#define MPPT_END_FRAME_ID                        (0x47fu)       /* standard, sender: MPPT */
#define COOLINGBACK_NODE_FRAME_ID                (0x4e0u)       /* standard, sender: CoolingBack */
#define COOLINGBACK_FAN_FRAME_ID                 (0x4e1u)       /* standard, sender: CoolingBack */
#define COOLINGBACK_END_FRAME_ID                 (0x4ffu)       /* standard, sender: CoolingBack */
#define COOLINGLEFT_NODE_FRAME_ID                (0x500u)       /* standard, sender: CoolingLeft */
#define COOLINGLEFT_SENSOR_FRAME_ID              (0x501u)       /* standard, sender: CoolingLeft */
#define COOLINGLEFT_FAN_FRAME_ID                 (0x502u)       /* standard, sender: CoolingLeft */
#define COOLINGLEFT_SERWO_FRAME_ID               (0x503u)       /* standard, sender: CoolingLeft */
#define COOLINGLEFT_END_FRAME_ID                 (0x51fu)       /* standard, sender: CoolingLeft */
#define COOLINGRIGHT_NODE_FRAME_ID               (0x520u)       /* standard, sender: CoolingRight */
#define COOLINGRIGHT_SENSOR_FRAME_ID             (0x521u)       /* standard, sender: CoolingRight */
#define COOLINGRIGHT_FAN_FRAME_ID                (0x522u)       /* standard, sender: CoolingRight */
#define COOLINGRIGHT_SERWO_FRAME_ID              (0x523u)       /* standard, sender: CoolingRight */
#define COOLINGRIGHT_END_FRAME_ID                (0x53fu)       /* standard, sender: CoolingRight */
#define COOLINGMOTOR_NODE_FRAME_ID               (0x540u)       /* standard, sender: CoolingMotor */
#define COOLINGMOTOR_SENSOR_FRAME_ID             (0x541u)       /* standard, sender: CoolingMotor */
#define COOLINGMOTOR_FAN_FRAME_ID                (0x542u)       /* standard, sender: CoolingMotor */
#define COOLINGMOTOR_SERWO_FRAME_ID              (0x543u)       /* standard, sender: CoolingMotor */
#define COOLINGMOTOR_END_FRAME_ID                (0x55fu)       /* standard, sender: CoolingMotor */
#define LOWVOLTCONVERTER_NODE_FRAME_ID           (0x5c0u)       /* standard, sender: Converter */
#define LOWVOLTCONVERTER_END_FRAME_ID            (0x5dfu)       /* standard, sender: Converter */
#define SENSORFR_NODE_FRAME_ID                   (0x640u)       /* standard, sender: SensorFR */
#define SENSORFR_WHEEL_SPEED_FRAME_ID            (0x641u)       /* standard, sender: SensorFR */
#define SENSORFR_SUSPENSION_FRAME_ID             (0x642u)       /* standard, sender: SensorFR */
#define SENSORFR_DOOR_SENSOR_FRAME_ID            (0x643u)       /* standard, sender: SensorFR */
#define SENSORFR_END_FRAME_ID                    (0x65fu)       /* standard, sender: SensorFR */
#define SENSORFL_NODE_FRAME_ID                   (0x660u)       /* standard, sender: SensorFL */
#define SENSORFL_WHEEL_SPEED_FRAME_ID            (0x661u)       /* standard, sender: SensorFL */
#define SENSORFL_SUSPENSION_FRAME_ID             (0x662u)       /* standard, sender: SensorFL */
#define SENSORFL_DOOR_SENSOR_FRAME_ID            (0x663u)       /* standard, sender: SensorFL */
#define SENSORFL_END_FRAME_ID                    (0x675u)       /* standard, sender: SensorFL */
#define SENSORRR_NODE_FRAME_ID                   (0x680u)       /* standard, sender: SensorRR */
#define SENSORRR_WHEEL_SPEED_FRAME_ID            (0x681u)       /* standard, sender: SensorRR */
#define SENSORRR_SUSPENSION_FRAME_ID             (0x682u)       /* standard, sender: SensorRR */
#define SENSORRR_DOOR_SENSOR_FRAME_ID            (0x683u)       /* standard, sender: SensorRR */
#define SENSORRR_END_FRAME_ID                    (0x69fu)       /* standard, sender: SensorRR */
#define SENSORRL_NODE_FRAME_ID                   (0x6a0u)       /* standard, sender: SensorRL */
#define SENSORRL_WHEEL_SPEED_FRAME_ID            (0x6a1u)       /* standard, sender: SensorRL */
#define SENSORRL_SUSPENSION_FRAME_ID             (0x6a2u)       /* standard, sender: SensorRL */
#define SENSORRL_DOOR_SENSOR_FRAME_ID            (0x6a3u)       /* standard, sender: SensorRL */
#define SENSORRL_END_FRAME_ID                    (0x6bfu)       /* standard, sender: SensorRL */
#define ENGINELEFT_STATIC_NMT_FRAME_ID           (0x726u)       /* standard, sender: EngineLeft */
#define ENGINERIGHT_STATIC_NMT_FRAME_ID          (0x727u)       /* standard, sender: EngineRight */
#define LIGHTSFR_NODE_FRAME_ID                   (0x740u)       /* standard, sender: LightsFR */
#define LIGHTSFR_STATUS_FRAME_ID                 (0x741u)       /* standard, sender: LightsFR */
#define LIGHTSFR_END_FRAME_ID                    (0x75fu)       /* standard, sender: LightsFR */
#define LIGHTSFL_NODE_FRAME_ID                   (0x760u)       /* standard, sender: LightsFL */
#define LIGHTSFL_STATUS_FRAME_ID                 (0x761u)       /* standard, sender: LightsFL */
#define LIGHTSFL_END_FRAME_ID                    (0x77fu)       /* standard, sender: LightsFL */
#define LIGHTSRR_NODE_FRAME_ID                   (0x780u)       /* standard, sender: LightsRR */
#define LIGHTSRR_STATUS_FRAME_ID                 (0x781u)       /* standard, sender: LightsRR */
#define LIGHTSRR_END_FRAME_ID                    (0x79fu)       /* standard, sender: LightsRR */
#define LIGHTSRL_NODE_FRAME_ID                   (0x7a0u)       /* standard, sender: LightsRL */
#define LIGHTSRL_STATUS_FRAME_ID                 (0x7a1u)       /* standard, sender: LightsRL */
#define LIGHTSRL_END_FRAME_ID                    (0x7bfu)       /* standard, sender: LightsRL */
#define RCD_STATIC_CHARGER1COMMS_FRAME_ID        (0x1806e5f4u)  /* extended, sender: RCD */
#define RCD_STATIC_CHARGER2COMMS_FRAME_ID        (0x1806e7f4u)  /* extended, sender: RCD */
#define RCD_STATIC_CHARGER3COMMS_FRAME_ID        (0x1806e8f4u)  /* extended, sender: RCD */
#define CHARGER1_STATIC_OUT_FRAME_ID             (0x18ff50e5u)  /* extended, sender: Charger1 */
#define CHARGER2_STATIC_OUT_FRAME_ID             (0x18ff50e7u)  /* extended, sender: Charger2 */
#define CHARGER3_STATIC_OUT_FRAME_ID             (0x18ff50e8u)  /* extended, sender: Charger3 */

#endif /* INC_CAN_ID_LIST_H_ */

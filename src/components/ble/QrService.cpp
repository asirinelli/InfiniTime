#include "QrService.h"
#include "systemtask/SystemTask.h"


int QRCallback(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg) {
  auto qrService = static_cast<Pinetime::Controllers::QrService *>(arg);
  return qrService->OnCommand(conn_handle, attr_handle, ctxt);
}

Pinetime::Controllers::QrService::QrService(Pinetime::System::SystemTask &system) : m_system(system) {
  qrsTextCharUuid.value[11] = qrsTextCharId[0];
  qrsTextCharUuid.value[12] = qrsTextCharId[1];

  characteristicDefinition[0] = {.uuid = (ble_uuid_t *) (&qrsTextCharUuid),
      .access_cb = QRCallback,
      .arg = this,
      .flags = BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_READ
  };
  characteristicDefinition[1] = {0};

  serviceDefinition[0] = {
      .type = BLE_GATT_SVC_TYPE_PRIMARY,
      .uuid = (ble_uuid_t *) &qrsUuid,
      .characteristics = characteristicDefinition
  };
  serviceDefinition[1] = {0};
}

void Pinetime::Controllers::QrService::Init() {
  int res = 0;
  res = ble_gatts_count_cfg(serviceDefinition);
  ASSERT(res == 0);

  res = ble_gatts_add_svcs(serviceDefinition);
  ASSERT(res == 0);
}

int Pinetime::Controllers::QrService::OnCommand(uint16_t conn_handle, uint16_t attr_handle,
                                                   struct ble_gatt_access_ctxt *ctxt) {
  if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
    size_t notifSize = OS_MBUF_PKTLEN(ctxt->om);
    uint8_t data[notifSize + 1];
    data[notifSize] = '\0';
    os_mbuf_copydata(ctxt->om, 0, notifSize, data);
    char *s = (char *) &data[0];
    NRF_LOG_INFO("DATA : %s", s);
    if (ble_uuid_cmp(ctxt->chr->uuid, (ble_uuid_t *) &qrsTextCharUuid) == 0) {
      qrText = s;
    }
  }
  return 0;
}

std::string Pinetime::Controllers::QrService::getQrText() {
  return qrText;
}

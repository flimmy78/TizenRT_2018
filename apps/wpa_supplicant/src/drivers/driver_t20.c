/*
 * Interaction with the T20 driver
 * Copyright (c) 2016, Samsung Electronics Co., Ltd.
 */

#include "includes.h"
#include "driver.h"

#ifdef CONFIG_SCSC_WLAN
extern void *slsi_t20_init(void *ctx, const char *ifname, void *global_priv);
extern void slsi_t20_deinit(void *priv);
extern const u8 *slsi_get_mac_addr(void *priv);
extern int slsi_t20_get_capa(void *priv, struct wpa_driver_capa *capa);
extern int slsi_hw_scan(void *priv, struct wpa_driver_scan_params *params);
extern struct wpa_scan_results *slsi_get_scan_results(void *priv);
extern int slsi_connect(void *priv, struct wpa_driver_associate_params *params);
extern int slsi_disconnect(void *priv, const u8 *addr, int reason_code);
extern int slsi_start_ap(void *priv, struct wpa_driver_ap_params *settings);
extern int slsi_stop_ap(void *priv);
extern int slsi_del_station(void *priv, const u8 *addr, int reason);
extern ssize_t slsi_set_country(void *priv, const char *country_code);
extern ssize_t slsi_get_country(void *priv, char *country_code);
extern int slsi_set_rts(void *priv, int rts);
extern int slsi_get_signal_poll(void *priv, struct wpa_signal_info *si);
extern int slsi_set_frag_threshold(void *priv, int frag_threshold);
extern int slsi_get_ap_bssid(void *priv, u8 *bssid);
extern struct hostapd_hw_modes *slsi_get_hw_feature_data(void *priv, u16 *num_modes, u16 *flags);

extern int slsi_mlme_send_ap_eapol(void *priv, const u8 *addr, const u8 *data, size_t data_len, int encrypt, const u8 *own_addr, u32 flags);
extern int slsi_get_key(const char *ifname, void *priv, const u8 *addr, int idx, u8 *seq);
extern int slsi_set_tx_power(void *priv, int dbm);
extern int slsi_get_tx_power(void *priv);
extern int slsi_set_panic(void *priv);

extern int slsi_add_key(const char *ifname, void *priv, enum wpa_alg alg, const u8 *mac_addr, int key_idx, int set_tx, const u8 *seq, size_t seq_len, const u8 *key, size_t key_len);
extern int slsi_get_ssid(void *priv, u8 *ssid);

#ifdef CONFIG_SLSI_WLAN_P2P
extern int slsi_remain_on_channel(void *priv, unsigned int freq, unsigned int duration);
extern int slsi_cancel_remain_on_channel(void *priv);
extern int slsi_mgmt_tx(void *priv, unsigned int freq, unsigned int wait, const u8 *dst, const u8 *src, const u8 *bssid, const u8 *data, size_t data_len, int no_cck);
extern void slsi_mgmt_tx_cancel_wait(void *priv);
extern int slsi_set_p2p_powersave(void *priv, int legacy_ps, int opp_ps, int ctwindow);
extern int slsi_set_ap_wps_ie(void *priv, const struct wpabuf *beacon, const struct wpabuf *proberesp, const struct wpabuf *assocresp);
extern int slsi_add_virtual_intf(void *priv, enum wpa_driver_if_type type, const char *ifname, const u8 *addr, void *bss_ctx, void **drv_priv, char *force_ifname, u8 *if_addr, const char *bridge, int use_existing);
extern int slsi_del_virtual_intf(void *priv, enum wpa_driver_if_type type, const char *ifname);
#endif							/*CONFIG_SLSI_WLAN_P2P */

int slsi_sta_remove(void *priv, const u8 *addr)
{
	return slsi_del_station(priv, addr, 0);
}

int slsi_sta_deauth(void *priv, const u8 *own_addr, const u8 *addr, int reason)
{
	return slsi_del_station(priv, addr, reason);
}

const struct wpa_driver_ops wpa_driver_t20_ops = {
	.name = "slsi_t20",
	.desc = "SLSI T20 Driver",
	.init2 = slsi_t20_init,
	.deinit = slsi_t20_deinit,
	.get_mac_addr = slsi_get_mac_addr,
	.get_capa = slsi_t20_get_capa,
	.scan2 = slsi_hw_scan,
	.get_scan_results2 = slsi_get_scan_results,
	.associate = slsi_connect,
	.deauthenticate = slsi_disconnect,
	.set_ap = slsi_start_ap,
	.stop_ap = slsi_stop_ap,
	.sta_remove = slsi_sta_remove,
	.sta_deauth = slsi_sta_deauth,
	.set_frag = slsi_set_frag_threshold,
	.set_rts = slsi_set_rts,
	.signal_poll = slsi_get_signal_poll,
	.get_country = slsi_get_country,
	.set_country = slsi_set_country,
	.get_bssid = slsi_get_ap_bssid,
	.get_hw_feature_data = slsi_get_hw_feature_data,
	.set_key = slsi_add_key,
	.get_ssid = slsi_get_ssid,
	.hapd_send_eapol = slsi_mlme_send_ap_eapol,
	.get_seqnum = slsi_get_key,
	.set_tx_power = slsi_set_tx_power,
	.get_tx_power = slsi_get_tx_power,
	.set_panic = slsi_set_panic,
#ifdef CONFIG_SLSI_WLAN_P2P
	.remain_on_channel = slsi_remain_on_channel,
	.cancel_remain_on_channel = slsi_cancel_remain_on_channel,
	.send_action = slsi_mgmt_tx,
	.send_action_cancel_wait = slsi_mgmt_tx_cancel_wait,
	.set_p2p_powersave = slsi_set_p2p_powersave,
	.set_ap_wps_ie = slsi_set_ap_wps_ie,
	.if_add = slsi_add_virtual_intf,
	.if_remove = slsi_del_virtual_intf,
#endif							/*CONFIG_SLSI_WLAN_P2P */
};
#else
int slsi_sta_remove(void *priv, const u8 *addr)
{
	return 0;
}

int slsi_sta_deauth(void *priv, const u8 *own_addr, const u8 *addr, int reason)
{
	return 0;
}

const struct wpa_driver_ops wpa_driver_t20_ops = {
	.name = "slsi_t20",
	.desc = "SLSI T20 Driver",
};
#endif

/*
    pmacct (Promiscuous mode IP Accounting package)
    pmacct is Copyright (C) 2003-2009 by Paolo Lucente
*/

/*
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

/* defines */
#define PLUGIN_ID_CORE          0
#define PLUGIN_ID_MEMORY        1
#define PLUGIN_ID_PRINT         2
#define PLUGIN_ID_NFPROBE       3
#define PLUGIN_ID_SFPROBE       4
#define PLUGIN_ID_MYSQL		5 
#define PLUGIN_ID_PGSQL         6
#define PLUGIN_ID_SQLITE3       7
#define PLUGIN_ID_UNKNOWN       -1

/* vars */
int protocols_number;

/* structures */

static const struct _protocols_struct _protocols[] = {
  {"ip", 0},
  {"icmp", 1},
  {"igmp", 2},
  {"ggp", 3},
  {"4", 4},
  {"5", 5},
  {"tcp", 6},
  {"7", 7},
  {"egp", 8},
  {"igp", 9},
  {"10", 10},
  {"11", 11},
  {"12", 12},
  {"13", 13},
  {"14", 14},
  {"15", 15},
  {"16", 16},
  {"udp", 17},
  {"mux", 18},
  {"19", 19},
  {"20", 20},
  {"21", 21},
  {"22", 22},
  {"23", 23},
  {"24", 24},
  {"25", 25},
  {"26", 26},
  {"27", 27},
  {"28", 28},
  {"29", 29},
  {"30", 30},
  {"31", 31},
  {"32", 32},
  {"33", 33},
  {"34", 34},
  {"35", 35},
  {"36", 36},
  {"37", 37},
  {"38", 38}, 
  {"39", 39},
  {"40", 40},
  {"ipv6", 41},
  {"42", 42},
  {"ipv6-route", 43},
  {"ipv6-frag", 44},
  {"45", 45},
  {"rsvp", 46},
  {"gre", 47},
  {"48", 48},
  {"49", 49},
  {"ipv6-crypt", 50}, 
  {"ipv6-auth", 51},
  {"52", 52}, 
  {"53", 53},  
  {"54", 54}, 
  {"mobile", 55},   
  {"tlsp", 56},
  {"57", 57}, 
  {"ipv6-icmp", 58},    
  {"ipv6-nonxt", 59},
  {"ipv6-opts", 60},
  {"61", 61},
  {"62", 62},
  {"63", 63},
  {"64", 64},     
  {"65", 65},  
  {"66", 66},
  {"67", 67}, 
  {"68", 68},
  {"69", 69},   
  {"70", 70},
  {"71", 71},  
  {"72", 72}, 
  {"73", 73},
  {"74", 74},
  {"75", 75},
  {"76", 76},  
  {"77", 77},
  {"78", 78}, 
  {"79", 79},  
  {"iso-ip", 80},
  {"81", 81}, 
  {"82", 82},
  {"vines", 83},
  {"84", 84},
  {"85", 85}, 
  {"86", 86},
  {"87", 87},  
  {"eigrp", 88},   
  {"ospf", 89},
  {"90", 90}, 
  {"larp", 91},
  {"92", 92}, 
  {"ax.25", 93},   
  {"ipip", 94},
  {"95", 95},
  {"96", 96},
  {"97", 97},    
  {"encap", 98},
  {"99", 99},
  {"100", 100},  
  {"101", 101}, 
  {"pnni", 102},
  {"pim", 103},
  {"104", 104},
  {"105", 105},  
  {"106", 106},
  {"107", 107},
  {"IPcomp", 108}, 
  {"109", 109},
  {"110", 110},  
  {"ipx-in-ip", 111},
  {"vrrp", 112},
  {"113", 113}, 
  {"114", 114},
  {"l2tp", 115},   
  {"116", 116},
  {"117", 117}, 
  {"118", 118},
  {"119", 119},
  {"120", 120},  
  {"121", 121}, 
  {"122", 122},
  {"123", 123},
  {"isis", 124},
  {"125", 125},  
  {"126", 126},
  {"127", 127},
  {"128", 128}, 
  {"129", 129},
  {"130", 130},
  {"131", 131}, 
  {"sctp", 132},
  {"fc", 133},
  {"", -1},
};

#ifdef __PMACCTD_C
static struct _devices_struct _devices[] = {
  {null_handler, DLT_NULL},
  {eth_handler, DLT_EN10MB},
  {ppp_handler, DLT_PPP},
  {fddi_handler, DLT_FDDI},
  {tr_handler, DLT_IEEE802},
#if defined DLT_IEEE802_11
  {ieee_802_11_handler, DLT_IEEE802_11}, 
#endif
#if defined DLT_LINUX_SLL
  {sll_handler, DLT_LINUX_SLL},
#endif
#if defined DLT_RAW
  {raw_handler, DLT_RAW},
#endif
#if defined DLT_C_HDLC
  {chdlc_handler, DLT_C_HDLC},
#endif
#ifdef DLT_HDLC
  {chdlc_handler, DLT_HDLC},
#endif
  {NULL, -1},
};
#endif

#ifdef __CFG_C
static const struct _dictionary_line dictionary[] = {
  {"debug", cfg_key_debug},
  {"syslog", cfg_key_syslog},
  {"logfile", cfg_key_logfile},
  {"pidfile", cfg_key_pidfile},
  {"daemonize", cfg_key_daemonize},
  {"aggregate", cfg_key_aggregate},
  {"snaplen", cfg_key_snaplen},
  {"aggregate_filter", cfg_key_aggregate_filter},
  {"promisc", cfg_key_promisc},
  {"pcap_filter", cfg_key_pcap_filter},
  {"plugins", NULL},
  {"plugin_pipe_size", cfg_key_plugin_pipe_size},
  {"plugin_buffer_size", cfg_key_plugin_buffer_size},
  {"interface", cfg_key_interface},
  {"interface_wait", cfg_key_interface_wait},
  {"savefile_wait", cfg_key_savefile_wait},
  {"networks_mask", cfg_key_networks_mask},
  {"networks_file", cfg_key_networks_file},
  {"networks_cache_entries", cfg_key_networks_cache_entries},
  {"refresh_maps", cfg_key_refresh_maps},
  {"ports_file", cfg_key_ports_file},
  {"imt_path", cfg_key_imt_path},
  {"imt_passwd", cfg_key_imt_passwd},
  {"imt_buckets", cfg_key_imt_buckets},
  {"imt_mem_pools_number", cfg_key_imt_mem_pools_number},
  {"imt_mem_pools_size", cfg_key_imt_mem_pools_size},
  {"sql_db", cfg_key_sql_db},
  {"sql_table", cfg_key_sql_table},
  {"sql_table_schema", cfg_key_sql_table_schema},
  {"sql_table_version", cfg_key_sql_table_version},
  {"sql_table_type", cfg_key_sql_table_type},
  {"sql_host", cfg_key_sql_host},
  {"sql_data", cfg_key_sql_data},
  {"sql_backup_host", cfg_key_sql_recovery_backup_host}, /* obsolete */
  {"sql_user", cfg_key_sql_user},
  {"sql_passwd", cfg_key_sql_passwd},
  {"sql_refresh_time", cfg_key_sql_refresh_time},
  {"sql_startup_delay", cfg_key_sql_startup_delay},
  {"sql_optimize_clauses", cfg_key_sql_optimize_clauses},
  {"sql_history", cfg_key_sql_history},
  {"sql_history_roundoff", cfg_key_sql_history_roundoff},
  {"sql_history_since_epoch", cfg_key_sql_history_since_epoch},
  {"sql_recovery_backup_host", cfg_key_sql_recovery_backup_host},
  {"sql_recovery_logfile", cfg_key_sql_recovery_logfile},
  {"sql_max_writers", cfg_key_sql_max_writers},
  {"sql_trigger_exec", cfg_key_sql_trigger_exec},
  {"sql_trigger_time", cfg_key_sql_trigger_time},
  {"sql_cache_entries", cfg_key_sql_cache_entries},
  {"sql_dont_try_update", cfg_key_sql_dont_try_update},
  {"sql_preprocess", cfg_key_sql_preprocess},
  {"sql_preprocess_type", cfg_key_sql_preprocess_type},
  {"sql_multi_values", cfg_key_sql_multi_values},
  {"sql_aggressive_classification", cfg_key_sql_aggressive_classification},
  {"sql_locking_style", cfg_key_sql_locking_style},
  {"sql_use_copy", cfg_key_sql_use_copy},
  {"print_refresh_time", cfg_key_print_refresh_time},
  {"print_cache_entries", cfg_key_print_cache_entries},
  {"print_markers", cfg_key_print_markers},
  {"nfacctd_port", cfg_key_nfacctd_port},
  {"nfacctd_ip", cfg_key_nfacctd_ip},
  {"nfacctd_allow_file", cfg_key_nfacctd_allow_file},
  {"nfacctd_time_secs", cfg_key_nfacctd_time_secs},
  {"nfacctd_time_new", cfg_key_nfacctd_time_new},
  {"nfacctd_as_new", cfg_key_nfacctd_as_new},
  {"nfacctd_mcast_groups", cfg_key_nfacctd_mcast_groups},
  {"nfacctd_sql_log", cfg_key_nfacctd_sql_log},
  {"pmacctd_force_frag_handling", cfg_key_pmacctd_force_frag_handling},
  {"pmacctd_frag_buffer_size", cfg_key_pmacctd_frag_buffer_size},
  {"pmacctd_flow_buffer_size", cfg_key_pmacctd_flow_buffer_size},
  {"pmacctd_flow_buffer_buckets", cfg_key_pmacctd_flow_buffer_buckets},
  {"pmacctd_conntrack_buffer_size", cfg_key_pmacctd_conntrack_buffer_size},
  {"pmacctd_flow_lifetime", cfg_key_pmacctd_flow_lifetime},
  {"pmacctd_id", cfg_key_post_tag},	/* obsolete */
  {"nfacctd_id_file", cfg_key_pre_tag_map},	/* obsolete */
  {"pcap_savefile", cfg_key_pcap_savefile},
  {"pre_tag_map", cfg_key_pre_tag_map},	
  {"pre_tag_map_entries", cfg_key_pre_tag_map_entries},	
  {"pre_tag_filter", cfg_key_pre_tag_filter},
  {"post_tag", cfg_key_post_tag},
  {"sampling_rate", cfg_key_sampling_rate},
  {"sfacctd_port", cfg_key_nfacctd_port},
  {"sfacctd_ip", cfg_key_nfacctd_ip},
  {"sfacctd_allow_file", cfg_key_nfacctd_allow_file},
  {"sfacctd_as_new", cfg_key_nfacctd_as_new},
  {"sfacctd_renormalize", cfg_key_sfacctd_renormalize},
  {"nfacctd_renormalize", cfg_key_sfacctd_renormalize},
  {"nfacctd_disable_checks", cfg_key_nfacctd_disable_checks},
  {"sfacctd_disable_checks", cfg_key_nfacctd_disable_checks},
  {"sfacctd_mcast_groups", cfg_key_nfacctd_mcast_groups},
  {"classifiers", cfg_key_classifiers},
  {"classifier_tentatives", cfg_key_classifier_tentatives},
  {"classifier_table_num", cfg_key_classifier_table_num},
  {"nfprobe_timeouts", cfg_key_nfprobe_timeouts},
  {"nfprobe_hoplimit", cfg_key_nfprobe_hoplimit},
  {"nfprobe_maxflows", cfg_key_nfprobe_maxflows},
  {"nfprobe_receiver", cfg_key_nfprobe_receiver},
  {"nfprobe_engine", cfg_key_nfprobe_engine},
  {"nfprobe_version", cfg_key_nfprobe_version},
  {"sfprobe_receiver", cfg_key_sfprobe_receiver},
//  {"sfprobe_sampling_rate", cfg_key_sfprobe_sampling_rate},
  {"sfprobe_sampling_rate", cfg_key_sampling_rate},
  {"sfprobe_agentip", cfg_key_sfprobe_agentip},
  {"sfprobe_agentsubid", cfg_key_sfprobe_agentsubid},
  {"flow_handling_threads", cfg_key_flow_handling_threads},
  {"bgp_daemon", cfg_key_nfacctd_bgp},
  {"bgp_daemon_ip", cfg_key_nfacctd_bgp_ip},
  {"bgp_daemon_port", cfg_key_nfacctd_bgp_port},
  {"bgp_daemon_max_peers", cfg_key_nfacctd_bgp_max_peers},
  {"bgp_daemon_msglog", cfg_key_nfacctd_bgp_msglog},
  {"bgp_aspath_radius", cfg_key_nfacctd_bgp_aspath_radius},
  {"bgp_stdcomm_pattern", cfg_key_nfacctd_bgp_stdcomm_pattern},
  {"bgp_extcomm_pattern", cfg_key_nfacctd_bgp_extcomm_pattern},
  {"bgp_peer_src_as_type", cfg_key_nfacctd_bgp_peer_src_as_type},
  {"bgp_peer_src_as_map", cfg_key_nfacctd_bgp_peer_src_as_map},
  {"bgp_agent_map", cfg_key_nfacctd_bgp_to_agent_map},
  {"bgp_follow_default", cfg_key_nfacctd_bgp_follow_default},
  {"", NULL},
};

static struct plugin_type_entry plugin_types_list[] = {
  {PLUGIN_ID_CORE, 	"core", 	NULL},
  {PLUGIN_ID_MEMORY, 	"memory", 	imt_plugin},
  {PLUGIN_ID_PRINT,	"print",	print_plugin},
  {PLUGIN_ID_NFPROBE,	"nfprobe",	nfprobe_plugin},
  {PLUGIN_ID_SFPROBE,	"sfprobe",	sfprobe_plugin},
#ifdef WITH_MYSQL
  {PLUGIN_ID_MYSQL,	"mysql",	mysql_plugin},
#endif
#ifdef WITH_PGSQL
  {PLUGIN_ID_PGSQL,	"pgsql",	pgsql_plugin},
#endif
#ifdef WITH_SQLITE3
  {PLUGIN_ID_SQLITE3,	"sqlite3",	sqlite3_plugin},
#endif
  {PLUGIN_ID_UNKNOWN,	"",		NULL},
};

#endif
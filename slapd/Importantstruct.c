// TODO: Under satand the BER stuff
// Involded function ber_scanf
struct berelement {
}

struct Operation {
  // Runtime indicates starting time of the opeartion
  time o_qtime;
  
  // The thread which is processing the opearion
  thread_id o_tid;
  
  // Indicates what type of opeartion, but code wriiten in pre-historic times 
  // used int #DEFINES and even stupier int type defs to make it look more confusing
  // LDAP_REQ_BIND = 96
  ber_tag_t o_tag; 
  
  // "Context"
  void* 	o_tmpmemctx;
  
  // Seems like the socket connection
  connection o_connection;
};

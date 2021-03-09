
struct mayaT {
  double mayaT_baktun;
  double mayaT_katun;
  double mayaT_tun;
  double mayaT_uinal;
  double mayaT_kin;
};

double get_working_time (void);
struct mayaT from_working_time_to_maya (double wt);
void print_long_round(struct mayaT *mt);

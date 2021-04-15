
struct mayaT {
  double mayaT_baktun;
  double mayaT_katun;
  double mayaT_tun;
  double mayaT_uinal;
  double mayaT_kin;
};

double get_working_time (void);
void from_working_time_to_maya (double wt, struct mayaT *mt);
void print_calendar_round (int working_time);
void print_long_round(struct mayaT *mt);
int calc_total_draw_size(int number);
void fill_mayaT (struct mayaT *mt); /* Currently unused */
void mprint(int num); /* Currently unused */
void convert(int num); /* Currently unused */
void string2maya (char *instr, struct mayaT *mt);
void add_dates_all (struct mayaT *may_ptr, int size, int beg, int use_ct);
void substract_dates_all (struct mayaT *may_ptr, int size, int beg, int use_ct);

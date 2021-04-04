/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__hpca2
#define _nrn_initial _nrn_initial__hpca2
#define nrn_cur _nrn_cur__hpca2
#define _nrn_current _nrn_current__hpca2
#define nrn_jacob _nrn_jacob__hpca2
#define nrn_state _nrn_state__hpca2
#define _net_receive _net_receive__hpca2 
#define rates rates__hpca2 
#define states1 states1__hpca2 
#define scheme1 scheme1__hpca2 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define gbar _p[0]
#define ica_pmp _p[1]
#define ica_basal _p[2]
#define ik _p[3]
#define ca _p[4]
#define HPCA _p[5]
#define CaHPCA _p[6]
#define Ca2HPCA _p[7]
#define HPCA_m _p[8]
#define pump _p[9]
#define pumpca _p[10]
#define n _p[11]
#define HPCA_z _p[12]
#define CaHPCA_z _p[13]
#define Ca2HPCA_z _p[14]
#define HPCA_m_z _p[15]
#define HPCA_tot_z _p[16]
#define Bufer _p[17]
#define CaBufer _p[18]
#define ica _p[19]
#define drive_channels _p[20]
#define cai _p[21]
#define Vol _p[22]
#define k_ins _p[23]
#define ica_balance _p[24]
#define B0 _p[25]
#define HP0 _p[26]
#define cao _p[27]
#define ica_pmp_last _p[28]
#define parea _p[29]
#define a _p[30]
#define b _p[31]
#define gk _p[32]
#define ek _p[33]
#define ninf _p[34]
#define ntau _p[35]
#define Dca _p[36]
#define DHPCA _p[37]
#define DCaHPCA _p[38]
#define DCa2HPCA _p[39]
#define DHPCA_m _p[40]
#define Dpump _p[41]
#define Dpumpca _p[42]
#define Dn _p[43]
#define DHPCA_z _p[44]
#define DCaHPCA_z _p[45]
#define DCa2HPCA_z _p[46]
#define DHPCA_m_z _p[47]
#define DHPCA_tot_z _p[48]
#define DBufer _p[49]
#define DCaBufer _p[50]
#define v _p[51]
#define _g _p[52]
#define _ion_cao	*_ppvar[0]._pval
#define _ion_ica	*_ppvar[1]._pval
#define _ion_cai	*_ppvar[2]._pval
#define _ion_dicadv	*_ppvar[3]._pval
#define _style_ca	*((int*)_ppvar[4]._pvoid)
#define _ion_ek	*_ppvar[5]._pval
#define _ion_ik	*_ppvar[6]._pval
#define _ion_dikdv	*_ppvar[7]._pval
#define diam	*_ppvar[8]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_rates(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_hpca2", _hoc_setdata,
 "rates_hpca2", _hoc_rates,
 0, 0
};
 #define _zdsq _thread[2]._pval[0]
 #define _zdsqvol _thread[2]._pval[1]
 #define _zr _thread[2]._pval[2]
 #define _zica_basal _thread[2]._pval[3]
 /* declare global and static user variables */
 static int _thread1data_inuse = 0;
static double _thread1data[1];
#define _gth 3
#define Bufer0 Bufer0_hpca2
 double Bufer0 = 0.18;
#define D D_hpca2
 double D = 40;
#define Rb Rb_hpca2
 double Rb = 0.02;
#define Ra Ra_hpca2
 double Ra = 0.01;
#define TotalPump TotalPump_hpca2
 double TotalPump = 1e-11;
#define TotalHPCA TotalHPCA_hpca2
 double TotalHPCA = 0.03821;
#define caix caix_hpca2
 double caix = 1;
#define cai0 cai0_hpca2
 double cai0 = 0.0001;
#define delta delta_hpca2
 double delta = 0.1;
#define k4Pump k4Pump_hpca2
 double k4Pump = 0.0003;
#define k3Pump k3Pump_hpca2
 double k3Pump = 1;
#define k2Pump k2Pump_hpca2
 double k2Pump = 0.0003;
#define k1Pump k1Pump_hpca2
 double k1Pump = 1;
#define k2bufer k2bufer_hpca2
 double k2bufer = 1;
#define k1bufer k1bufer_hpca2
 double k1bufer = 10;
#define k_out k_out_hpca2
 double k_out = 0.002;
#define k4HPCA k4HPCA_hpca2
 double k4HPCA = 0.01;
#define k3HPCA k3HPCA_hpca2
 double k3HPCA = 16.67;
#define k2HPCA k2HPCA_hpca2
 double k2HPCA = 0.01;
#define k1HPCA k1HPCA_hpca2
 double k1HPCA = 15;
#define q10 q10_hpca2
 double q10 = 2.3;
#define tau_d tau_d_hpca2
 double tau_d = 200;
#define tadj_hpca2 _thread1data[0]
#define tadj _thread[_gth]._pval[0]
#define temp temp_hpca2
 double temp = 36;
#define vmax vmax_hpca2
 double vmax = 100;
#define vmin vmin_hpca2
 double vmin = -120;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "k1HPCA_hpca2", "/mM-ms",
 "k2HPCA_hpca2", "/ms",
 "k3HPCA_hpca2", "/mM-ms",
 "k4HPCA_hpca2", "/ms",
 "k_out_hpca2", "/ms",
 "TotalHPCA_hpca2", "mM",
 "D_hpca2", "um2/s",
 "Bufer0_hpca2", "mM",
 "k1bufer_hpca2", "/mM-ms",
 "k2bufer_hpca2", "/ms",
 "k1Pump_hpca2", "/mM-ms",
 "k2Pump_hpca2", "/ms",
 "k3Pump_hpca2", "/ms",
 "k4Pump_hpca2", "/mM-ms",
 "TotalPump_hpca2", "mol/cm2",
 "cai0_hpca2", "mM",
 "tau_d_hpca2", "ms",
 "delta_hpca2", "um",
 "Ra_hpca2", "cm2/mol-ms",
 "Rb_hpca2", "/ms",
 "temp_hpca2", "degC",
 "vmin_hpca2", "mV",
 "vmax_hpca2", "mV",
 "gbar_hpca2", "pS/um2",
 "ca_hpca2", "mM",
 "HPCA_hpca2", "mM",
 "CaHPCA_hpca2", "mM",
 "Ca2HPCA_hpca2", "mM",
 "HPCA_m_hpca2", "mol/cm2",
 "pump_hpca2", "mol/cm2",
 "pumpca_hpca2", "mol/cm2",
 "HPCA_z_hpca2", "mM",
 "CaHPCA_z_hpca2", "mM",
 "Ca2HPCA_z_hpca2", "mM",
 "HPCA_m_z_hpca2", "mM",
 "HPCA_tot_z_hpca2", "mM",
 "Bufer_hpca2", "mM",
 "CaBufer_hpca2", "mM",
 "ica_pmp_hpca2", "mA/cm2",
 "ica_basal_hpca2", "mA/cm2",
 "ik_hpca2", "mA/cm2",
 0,0
};
 static double CaBufer0 = 0;
 static double Ca2HPCA_z0 = 0;
 static double CaHPCA_z0 = 0;
 static double Ca2HPCA0 = 0;
 static double CaHPCA0 = 0;
 static double HPCA_tot_z0 = 0;
 static double HPCA_m_z0 = 0;
 static double HPCA_z0 = 0;
 static double HPCA_m0 = 0;
 static double HPCA0 = 0;
 static double ca0 = 0;
 static double delta_t = 0.01;
 static double n0 = 0;
 static double pumpca0 = 0;
 static double pump0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "k1HPCA_hpca2", &k1HPCA_hpca2,
 "k2HPCA_hpca2", &k2HPCA_hpca2,
 "k3HPCA_hpca2", &k3HPCA_hpca2,
 "k4HPCA_hpca2", &k4HPCA_hpca2,
 "k_out_hpca2", &k_out_hpca2,
 "TotalHPCA_hpca2", &TotalHPCA_hpca2,
 "D_hpca2", &D_hpca2,
 "Bufer0_hpca2", &Bufer0_hpca2,
 "k1bufer_hpca2", &k1bufer_hpca2,
 "k2bufer_hpca2", &k2bufer_hpca2,
 "k1Pump_hpca2", &k1Pump_hpca2,
 "k2Pump_hpca2", &k2Pump_hpca2,
 "k3Pump_hpca2", &k3Pump_hpca2,
 "k4Pump_hpca2", &k4Pump_hpca2,
 "TotalPump_hpca2", &TotalPump_hpca2,
 "cai0_hpca2", &cai0_hpca2,
 "tau_d_hpca2", &tau_d_hpca2,
 "delta_hpca2", &delta_hpca2,
 "caix_hpca2", &caix_hpca2,
 "Ra_hpca2", &Ra_hpca2,
 "Rb_hpca2", &Rb_hpca2,
 "temp_hpca2", &temp_hpca2,
 "q10_hpca2", &q10_hpca2,
 "vmin_hpca2", &vmin_hpca2,
 "vmax_hpca2", &vmax_hpca2,
 "tadj_hpca2", &tadj_hpca2,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"hpca2",
 "gbar_hpca2",
 0,
 "ica_pmp_hpca2",
 "ica_basal_hpca2",
 "ik_hpca2",
 0,
 "ca_hpca2",
 "HPCA_hpca2",
 "CaHPCA_hpca2",
 "Ca2HPCA_hpca2",
 "HPCA_m_hpca2",
 "pump_hpca2",
 "pumpca_hpca2",
 "n_hpca2",
 "HPCA_z_hpca2",
 "CaHPCA_z_hpca2",
 "Ca2HPCA_z_hpca2",
 "HPCA_m_z_hpca2",
 "HPCA_tot_z_hpca2",
 "Bufer_hpca2",
 "CaBufer_hpca2",
 0,
 0};
 static Symbol* _morphology_sym;
 static Symbol* _ca_sym;
 static Symbol* _k_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 53, _prop);
 	/*initialize range parameters*/
 	gbar = 600;
 	_prop->param = _p;
 	_prop->param_size = 53;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 9, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_morphology_sym);
 	_ppvar[8]._pval = &prop_ion->param[0]; /* diam */
 prop_ion = need_memb(_ca_sym);
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_promote(prop_ion, 3, 0);
 	_ppvar[0]._pval = &prop_ion->param[2]; /* cao */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[2]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 	_ppvar[4]._pvoid = (void*)(&(prop_ion->dparam[0]._i)); /* iontype for ca */
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[5]._pval = &prop_ion->param[0]; /* ek */
 	_ppvar[6]._pval = &prop_ion->param[3]; /* ik */
 	_ppvar[7]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static void _initlists();
 static void _thread_mem_init(Datum*);
 static void _thread_cleanup(Datum*);
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _hpca2_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	ion_reg("k", -10000.);
 	_morphology_sym = hoc_lookup("morphology");
 	_ca_sym = hoc_lookup("ca_ion");
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 5);
  _extcall_thread = (Datum*)ecalloc(4, sizeof(Datum));
  _thread_mem_init(_extcall_thread);
  _thread1data_inuse = 0;
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 1, _thread_mem_init);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 53, 9);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "#ca_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 6, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 7, "k_ion");
  hoc_register_dparam_semantics(_mechtype, 8, "diam");
 	nrn_writes_conc(_mechtype, 0);
 	hoc_register_cvode(_mechtype, _ode_count, 0, 0, 0);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 hpca2 /home/arsentii/hippocalcin/HPCA-CA1/mechanism/hpca2.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 9.64853;
 static double PI = 3.14159;
 static double volo = 1e10;
 /*Top LOCAL _zdsq , _zdsqvol , _zr */
 /*Top LOCAL _zica_basal */
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsproto_);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 extern double *_nrn_thread_getelm();
 
#define _MATELM2(_row,_col) *(_nrn_thread_getelm(_so, _row + 1, _col + 1))
 
#define _RHS2(_arg) _rhs[_arg+1]
  
#define _linmat2  0
 static int _spth2 = 1;
 static int _cvspth2 = 0;
 
static int _ode_spec2(_threadargsproto_);
/*static int _ode_matsol2(_threadargsproto_);*/
 static int _slist2[9], _dlist2[9]; static double *_temp2;
 static int scheme1();
 static int _slist1[1], _dlist1[1];
 static int states1(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   cai = ca ;
   rates ( _threadargs_ ) ;
   Dn = ( ninf - n ) / ntau ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 cai = ca ;
 rates ( _threadargs_ ) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ntau )) ;
  return 0;
}
 /*END CVODE*/
 static int states1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   cai = ca ;
   rates ( _threadargs_ ) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ntau)))*(- ( ( ( ninf ) ) / ntau ) / ( ( ( ( - 1.0 ) ) ) / ntau ) - n) ;
   }
  return 0;
}
 
static int scheme1 (void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<9;_i++){
  	_RHS2(_i) = -_dt1*(_p[_slist2[_i]] - _p[_dlist2[_i]]);
	_MATELM2(_i, _i) = _dt1;
      
}  
_RHS2(1) *= ( Vol) ;
_MATELM2(1, 1) *= ( Vol); 
_RHS2(2) *= ( Vol) ;
_MATELM2(2, 2) *= ( Vol); 
_RHS2(3) *= ( Vol) ;
_MATELM2(3, 3) *= ( Vol); 
_RHS2(4) *= ( Vol) ;
_MATELM2(4, 4) *= ( Vol); 
_RHS2(5) *= ( ( 1e10 ) * parea) ;
_MATELM2(5, 5) *= ( ( 1e10 ) * parea); 
_RHS2(6) *= ( Vol) ;
_MATELM2(6, 6) *= ( Vol); 
_RHS2(7) *= ( Vol) ;
_MATELM2(7, 7) *= ( Vol); 
_RHS2(8) *= ( ( 1e10 ) * parea) ;
_MATELM2(8, 8) *= ( ( 1e10 ) * parea);  }
 _zr = diam / 2.0 ;
   Vol = PI * _zr * _zr ;
   _zica_basal = 2.0 * FARADAY * ( k3Pump * TotalPump * cai0 * ( 1e5 ) / ( k2Pump / k1Pump ) ) ;
   k_ins = ( 1e-3 ) * ( D * 0.1 ) / ( pow( _zr , 2.0 ) ) ;
   /* COMPARTMENT ( 1e10 ) * parea {
     pump pumpca HPCA_m }
   */
 /* COMPARTMENT volo {
     }
   */
 /* COMPARTMENT Vol {
     ca HPCA CaHPCA Ca2HPCA Bufer CaBufer }
   */
 /* ~ ca + pump <-> pumpca ( k1Pump * parea * ( 1e10 ) , k2Pump * parea * ( 1e10 ) )*/
 f_flux =  k1Pump * parea * ( 1e10 ) * pump * ca ;
 b_flux =  k2Pump * parea * ( 1e10 ) * pumpca ;
 _RHS2( 8) -= (f_flux - b_flux);
 _RHS2( 7) -= (f_flux - b_flux);
 
 _term =  k1Pump * parea * ( 1e10 ) * ca ;
 _MATELM2( 8 ,8)  += _term;
 _MATELM2( 7 ,8)  += _term;
 _term =  k1Pump * parea * ( 1e10 ) * pump ;
 _MATELM2( 8 ,7)  += _term;
 _MATELM2( 7 ,7)  += _term;
 _term =  k2Pump * parea * ( 1e10 ) ;
 _MATELM2( 8 ,0)  -= _term;
 _MATELM2( 7 ,0)  -= _term;
 /*REACTION*/
  /* ~ pumpca <-> pump + cao ( k3Pump * parea * ( 1e10 ) , k4Pump * parea * ( 1e10 ) )*/
 f_flux =  k3Pump * parea * ( 1e10 ) * pumpca ;
 b_flux =  k4Pump * parea * ( 1e10 ) * cao * pump ;
 _RHS2( 8) += (f_flux - b_flux);
 
 _term =  k3Pump * parea * ( 1e10 ) ;
 _MATELM2( 8 ,0)  -= _term;
 _term =  k4Pump * parea * ( 1e10 ) * cao ;
 _MATELM2( 8 ,8)  += _term;
 /*REACTION*/
   /* pump + pumpca = TotalPump * parea * ( 1e10 ) */
 _RHS2(0) =  TotalPump * parea * ( 1e10 );
 _MATELM2(0, 0) = 1 * ( ( 1e10 ) * parea);
 _RHS2(0) -= pumpca * ( ( 1e10 ) * parea) ;
 _MATELM2(0, 8) = 1 * ( ( 1e10 ) * parea);
 _RHS2(0) -= pump * ( ( 1e10 ) * parea) ;
 /*CONSERVATION*/
 ica_pmp = 2.0 * FARADAY * ( f_flux - b_flux ) / parea ;
   /* ~ ca < < ( - ( ica - _zica_basal - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) )*/
 f_flux = b_flux = 0.;
 _RHS2( 7) += (b_flux =   ( - ( ica - _zica_basal - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) ) );
 /*FLUX*/
  /* ~ ca + HPCA <-> CaHPCA ( k1HPCA * Vol , k2HPCA * Vol )*/
 f_flux =  k1HPCA * Vol * HPCA * ca ;
 b_flux =  k2HPCA * Vol * CaHPCA ;
 _RHS2( 6) -= (f_flux - b_flux);
 _RHS2( 7) -= (f_flux - b_flux);
 _RHS2( 4) += (f_flux - b_flux);
 
 _term =  k1HPCA * Vol * ca ;
 _MATELM2( 6 ,6)  += _term;
 _MATELM2( 7 ,6)  += _term;
 _MATELM2( 4 ,6)  -= _term;
 _term =  k1HPCA * Vol * HPCA ;
 _MATELM2( 6 ,7)  += _term;
 _MATELM2( 7 ,7)  += _term;
 _MATELM2( 4 ,7)  -= _term;
 _term =  k2HPCA * Vol ;
 _MATELM2( 6 ,4)  -= _term;
 _MATELM2( 7 ,4)  -= _term;
 _MATELM2( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ ca + CaHPCA <-> Ca2HPCA ( k3HPCA * Vol , k4HPCA * Vol )*/
 f_flux =  k3HPCA * Vol * CaHPCA * ca ;
 b_flux =  k4HPCA * Vol * Ca2HPCA ;
 _RHS2( 4) -= (f_flux - b_flux);
 _RHS2( 7) -= (f_flux - b_flux);
 _RHS2( 3) += (f_flux - b_flux);
 
 _term =  k3HPCA * Vol * ca ;
 _MATELM2( 4 ,4)  += _term;
 _MATELM2( 7 ,4)  += _term;
 _MATELM2( 3 ,4)  -= _term;
 _term =  k3HPCA * Vol * CaHPCA ;
 _MATELM2( 4 ,7)  += _term;
 _MATELM2( 7 ,7)  += _term;
 _MATELM2( 3 ,7)  -= _term;
 _term =  k4HPCA * Vol ;
 _MATELM2( 4 ,3)  -= _term;
 _MATELM2( 7 ,3)  -= _term;
 _MATELM2( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ ca + Bufer <-> CaBufer ( k1bufer * Vol , k2bufer * Vol )*/
 f_flux =  k1bufer * Vol * Bufer * ca ;
 b_flux =  k2bufer * Vol * CaBufer ;
 _RHS2( 1) -= (f_flux - b_flux);
 _RHS2( 7) -= (f_flux - b_flux);
 _RHS2( 2) += (f_flux - b_flux);
 
 _term =  k1bufer * Vol * ca ;
 _MATELM2( 1 ,1)  += _term;
 _MATELM2( 7 ,1)  += _term;
 _MATELM2( 2 ,1)  -= _term;
 _term =  k1bufer * Vol * Bufer ;
 _MATELM2( 1 ,7)  += _term;
 _MATELM2( 7 ,7)  += _term;
 _MATELM2( 2 ,7)  -= _term;
 _term =  k2bufer * Vol ;
 _MATELM2( 1 ,2)  -= _term;
 _MATELM2( 7 ,2)  -= _term;
 _MATELM2( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ Ca2HPCA <-> HPCA_m ( k_ins * Vol , k_out * parea * ( 1e10 ) )*/
 f_flux =  k_ins * Vol * Ca2HPCA ;
 b_flux =  k_out * parea * ( 1e10 ) * HPCA_m ;
 _RHS2( 3) -= (f_flux - b_flux);
 _RHS2( 5) += (f_flux - b_flux);
 
 _term =  k_ins * Vol ;
 _MATELM2( 3 ,3)  += _term;
 _MATELM2( 5 ,3)  -= _term;
 _term =  k_out * parea * ( 1e10 ) ;
 _MATELM2( 3 ,5)  -= _term;
 _MATELM2( 5 ,5)  += _term;
 /*REACTION*/
  HPCA_z = HPCA * Vol ;
   CaHPCA_z = CaHPCA * Vol ;
   Ca2HPCA_z = Ca2HPCA * Vol ;
   HPCA_m_z = HPCA_m * parea * ( 1e10 ) ;
   HPCA_tot_z = HPCA_z + CaHPCA_z + Ca2HPCA_z + HPCA_m_z ;
     } return _reset;
 }
 
static int  rates ( _threadargsproto_ ) {
   a = Ra * HPCA_m * parea * ( 1e11 ) ;
   b = Rb ;
   tadj = pow( q10 , ( ( celsius - temp ) / 10.0 ) ) ;
   ntau = 1.0 / tadj / ( a + b ) ;
   ninf = a / ( a + b ) ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rates ( _p, _ppvar, _thread, _nt );
 hoc_retpushx(_r);
}
 
/*CVODE ode begin*/
 static int _ode_spec2(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<9;_i++) _p[_dlist2[_i]] = 0.0;}
 _zr = diam / 2.0 ;
 Vol = PI * _zr * _zr ;
 _zica_basal = 2.0 * FARADAY * ( k3Pump * TotalPump * cai0 * ( 1e5 ) / ( k2Pump / k1Pump ) ) ;
 k_ins = ( 1e-3 ) * ( D * 0.1 ) / ( pow( _zr , 2.0 ) ) ;
 /* COMPARTMENT ( 1e10 ) * parea {
   pump pumpca HPCA_m }
 */
 /* COMPARTMENT volo {
   }
 */
 /* COMPARTMENT Vol {
   ca HPCA CaHPCA Ca2HPCA Bufer CaBufer }
 */
 /* ~ ca + pump <-> pumpca ( k1Pump * parea * ( 1e10 ) , k2Pump * parea * ( 1e10 ) )*/
 f_flux =  k1Pump * parea * ( 1e10 ) * pump * ca ;
 b_flux =  k2Pump * parea * ( 1e10 ) * pumpca ;
 Dpump -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 Dpumpca += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ pumpca <-> pump + cao ( k3Pump * parea * ( 1e10 ) , k4Pump * parea * ( 1e10 ) )*/
 f_flux =  k3Pump * parea * ( 1e10 ) * pumpca ;
 b_flux =  k4Pump * parea * ( 1e10 ) * cao * pump ;
 Dpumpca -= (f_flux - b_flux);
 Dpump += (f_flux - b_flux);
 
 /*REACTION*/
   /* pump + pumpca = TotalPump * parea * ( 1e10 ) */
 /*CONSERVATION*/
 ica_pmp = 2.0 * FARADAY * ( f_flux - b_flux ) / parea ;
 /* ~ ca < < ( - ( ica - _zica_basal - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) )*/
 f_flux = b_flux = 0.;
 Dca += (b_flux =   ( - ( ica - _zica_basal - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) ) );
 /*FLUX*/
  /* ~ ca + HPCA <-> CaHPCA ( k1HPCA * Vol , k2HPCA * Vol )*/
 f_flux =  k1HPCA * Vol * HPCA * ca ;
 b_flux =  k2HPCA * Vol * CaHPCA ;
 DHPCA -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 DCaHPCA += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca + CaHPCA <-> Ca2HPCA ( k3HPCA * Vol , k4HPCA * Vol )*/
 f_flux =  k3HPCA * Vol * CaHPCA * ca ;
 b_flux =  k4HPCA * Vol * Ca2HPCA ;
 DCaHPCA -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 DCa2HPCA += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca + Bufer <-> CaBufer ( k1bufer * Vol , k2bufer * Vol )*/
 f_flux =  k1bufer * Vol * Bufer * ca ;
 b_flux =  k2bufer * Vol * CaBufer ;
 DBufer -= (f_flux - b_flux);
 Dca -= (f_flux - b_flux);
 DCaBufer += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ Ca2HPCA <-> HPCA_m ( k_ins * Vol , k_out * parea * ( 1e10 ) )*/
 f_flux =  k_ins * Vol * Ca2HPCA ;
 b_flux =  k_out * parea * ( 1e10 ) * HPCA_m ;
 DCa2HPCA -= (f_flux - b_flux);
 DHPCA_m += (f_flux - b_flux);
 
 /*REACTION*/
  HPCA_z = HPCA * Vol ;
 CaHPCA_z = CaHPCA * Vol ;
 Ca2HPCA_z = Ca2HPCA * Vol ;
 HPCA_m_z = HPCA_m * parea * ( 1e10 ) ;
 HPCA_tot_z = HPCA_z + CaHPCA_z + Ca2HPCA_z + HPCA_m_z ;
 _p[_dlist2[0]] /= ( ( 1e10 ) * parea);
 _p[_dlist2[1]] /= ( Vol);
 _p[_dlist2[2]] /= ( Vol);
 _p[_dlist2[3]] /= ( Vol);
 _p[_dlist2[4]] /= ( Vol);
 _p[_dlist2[5]] /= ( ( 1e10 ) * parea);
 _p[_dlist2[6]] /= ( Vol);
 _p[_dlist2[7]] /= ( Vol);
 _p[_dlist2[8]] /= ( ( 1e10 ) * parea);
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol2(void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<9;_i++){
  	_RHS2(_i) = _dt1*(_p[_dlist2[_i]]);
	_MATELM2(_i, _i) = _dt1;
      
}  
_RHS2(0) *= ( ( 1e10 ) * parea) ;
_MATELM2(0, 0) *= ( ( 1e10 ) * parea); 
_RHS2(1) *= ( Vol) ;
_MATELM2(1, 1) *= ( Vol); 
_RHS2(2) *= ( Vol) ;
_MATELM2(2, 2) *= ( Vol); 
_RHS2(3) *= ( Vol) ;
_MATELM2(3, 3) *= ( Vol); 
_RHS2(4) *= ( Vol) ;
_MATELM2(4, 4) *= ( Vol); 
_RHS2(5) *= ( ( 1e10 ) * parea) ;
_MATELM2(5, 5) *= ( ( 1e10 ) * parea); 
_RHS2(6) *= ( Vol) ;
_MATELM2(6, 6) *= ( Vol); 
_RHS2(7) *= ( Vol) ;
_MATELM2(7, 7) *= ( Vol); 
_RHS2(8) *= ( ( 1e10 ) * parea) ;
_MATELM2(8, 8) *= ( ( 1e10 ) * parea);  }
 _zr = diam / 2.0 ;
 Vol = PI * _zr * _zr ;
 _zica_basal = 2.0 * FARADAY * ( k3Pump * TotalPump * cai0 * ( 1e5 ) / ( k2Pump / k1Pump ) ) ;
 k_ins = ( 1e-3 ) * ( D * 0.1 ) / ( pow( _zr , 2.0 ) ) ;
 /* COMPARTMENT ( 1e10 ) * parea {
 pump pumpca HPCA_m }
 */
 /* COMPARTMENT volo {
 }
 */
 /* COMPARTMENT Vol {
 ca HPCA CaHPCA Ca2HPCA Bufer CaBufer }
 */
 /* ~ ca + pump <-> pumpca ( k1Pump * parea * ( 1e10 ) , k2Pump * parea * ( 1e10 ) )*/
 _term =  k1Pump * parea * ( 1e10 ) * ca ;
 _MATELM2( 8 ,8)  += _term;
 _MATELM2( 7 ,8)  += _term;
 _MATELM2( 0 ,8)  -= _term;
 _term =  k1Pump * parea * ( 1e10 ) * pump ;
 _MATELM2( 8 ,7)  += _term;
 _MATELM2( 7 ,7)  += _term;
 _MATELM2( 0 ,7)  -= _term;
 _term =  k2Pump * parea * ( 1e10 ) ;
 _MATELM2( 8 ,0)  -= _term;
 _MATELM2( 7 ,0)  -= _term;
 _MATELM2( 0 ,0)  += _term;
 /*REACTION*/
  /* ~ pumpca <-> pump + cao ( k3Pump * parea * ( 1e10 ) , k4Pump * parea * ( 1e10 ) )*/
 _term =  k3Pump * parea * ( 1e10 ) ;
 _MATELM2( 0 ,0)  += _term;
 _MATELM2( 8 ,0)  -= _term;
 _term =  k4Pump * parea * ( 1e10 ) * cao ;
 _MATELM2( 0 ,8)  -= _term;
 _MATELM2( 8 ,8)  += _term;
 /* ~ ca < < ( - ( ica - _zica_basal - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) )*/
 /*FLUX*/
  /* ~ ca + HPCA <-> CaHPCA ( k1HPCA * Vol , k2HPCA * Vol )*/
 _term =  k1HPCA * Vol * ca ;
 _MATELM2( 6 ,6)  += _term;
 _MATELM2( 7 ,6)  += _term;
 _MATELM2( 4 ,6)  -= _term;
 _term =  k1HPCA * Vol * HPCA ;
 _MATELM2( 6 ,7)  += _term;
 _MATELM2( 7 ,7)  += _term;
 _MATELM2( 4 ,7)  -= _term;
 _term =  k2HPCA * Vol ;
 _MATELM2( 6 ,4)  -= _term;
 _MATELM2( 7 ,4)  -= _term;
 _MATELM2( 4 ,4)  += _term;
 /*REACTION*/
  /* ~ ca + CaHPCA <-> Ca2HPCA ( k3HPCA * Vol , k4HPCA * Vol )*/
 _term =  k3HPCA * Vol * ca ;
 _MATELM2( 4 ,4)  += _term;
 _MATELM2( 7 ,4)  += _term;
 _MATELM2( 3 ,4)  -= _term;
 _term =  k3HPCA * Vol * CaHPCA ;
 _MATELM2( 4 ,7)  += _term;
 _MATELM2( 7 ,7)  += _term;
 _MATELM2( 3 ,7)  -= _term;
 _term =  k4HPCA * Vol ;
 _MATELM2( 4 ,3)  -= _term;
 _MATELM2( 7 ,3)  -= _term;
 _MATELM2( 3 ,3)  += _term;
 /*REACTION*/
  /* ~ ca + Bufer <-> CaBufer ( k1bufer * Vol , k2bufer * Vol )*/
 _term =  k1bufer * Vol * ca ;
 _MATELM2( 1 ,1)  += _term;
 _MATELM2( 7 ,1)  += _term;
 _MATELM2( 2 ,1)  -= _term;
 _term =  k1bufer * Vol * Bufer ;
 _MATELM2( 1 ,7)  += _term;
 _MATELM2( 7 ,7)  += _term;
 _MATELM2( 2 ,7)  -= _term;
 _term =  k2bufer * Vol ;
 _MATELM2( 1 ,2)  -= _term;
 _MATELM2( 7 ,2)  -= _term;
 _MATELM2( 2 ,2)  += _term;
 /*REACTION*/
  /* ~ Ca2HPCA <-> HPCA_m ( k_ins * Vol , k_out * parea * ( 1e10 ) )*/
 _term =  k_ins * Vol ;
 _MATELM2( 3 ,3)  += _term;
 _MATELM2( 5 ,3)  -= _term;
 _term =  k_out * parea * ( 1e10 ) ;
 _MATELM2( 3 ,5)  -= _term;
 _MATELM2( 5 ,5)  += _term;
 /*REACTION*/
  HPCA_z = HPCA * Vol ;
 CaHPCA_z = CaHPCA * Vol ;
 Ca2HPCA_z = Ca2HPCA * Vol ;
 HPCA_m_z = HPCA_m * parea * ( 1e10 ) ;
 HPCA_tot_z = HPCA_z + CaHPCA_z + Ca2HPCA_z + HPCA_m_z ;
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ hoc_execerror("hpca2", "cannot be used with CVODE"); return 0;}
 
static void _thread_mem_init(Datum* _thread) {
   _thread[2]._pval = (double*)ecalloc(4, sizeof(double));
  if (_thread1data_inuse) {_thread[_gth]._pval = (double*)ecalloc(1, sizeof(double));
 }else{
 _thread[_gth]._pval = _thread1data; _thread1data_inuse = 1;
 }
 }
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(_thread[_cvspth2]._pvoid);
   _nrn_destroy_sparseobj_thread(_thread[_spth2]._pvoid);
   free((void*)(_thread[2]._pval));
  if (_thread[_gth]._pval == _thread1data) {
   _thread1data_inuse = 0;
  }else{
   free((void*)_thread[_gth]._pval);
  }
 }
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 2);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 2, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 3, 4);
   nrn_update_ion_pointer(_k_sym, _ppvar, 5, 0);
   nrn_update_ion_pointer(_k_sym, _ppvar, 6, 3);
   nrn_update_ion_pointer(_k_sym, _ppvar, 7, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  Bufer = Bufer0;
  CaBufer = CaBufer0;
  Ca2HPCA_z = Ca2HPCA_z0;
  CaHPCA_z = CaHPCA_z0;
  Ca2HPCA = Ca2HPCA0;
  CaHPCA = CaHPCA0;
  HPCA_tot_z = HPCA_tot_z0;
  HPCA_z = HPCA_z0;
  HPCA_m = HPCA_m0;
  HPCA = HPCA0;
  HPCA_m_z = HPCA_m_z0;
  ca = ca0;
  n = n0;
  pumpca = pumpca0;
  pump = pump0;
 {
   cai = cai0 ;
   B0 = Bufer0 / ( 1.0 + ( cai * k1bufer / k2bufer ) ) ;
   ca = cai ;
   HPCA = TotalHPCA ;
   Bufer = B0 ;
   CaBufer = Bufer0 - B0 ;
   parea = PI * diam ;
   pump = TotalPump / ( 1.0 + ( cai * k1Pump / k2Pump ) ) ;
   pumpca = TotalPump - pump ;
   ica_pmp_last = 0.0 ;
   rates ( _threadargs_ ) ;
   n = ninf ;
   }
 
}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  cao = _ion_cao;
  ica = _ion_ica;
  cai = _ion_cai;
  cai = _ion_cai;
  ek = _ion_ek;
 initmodel(_p, _ppvar, _thread, _nt);
  _ion_cai = cai;
   nrn_wrote_conc(_ca_sym, (&(_ion_cai)) - 1, _style_ca);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   ica_pmp_last = ica_pmp ;
   ica = ica_pmp ;
   gk = tadj * gbar * n ;
   ik = ( 1e-4 ) * gk * ( v - ek ) ;
   }
 _current += ica;
 _current += ik;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  cao = _ion_cao;
  ica = _ion_ica;
  cai = _ion_cai;
  cai = _ion_cai;
  ek = _ion_ek;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dik;
 double _dica;
  _dica = ica;
  _dik = ik;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dicadv += (_dica - ica)/.001 ;
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_cai = cai;
  _ion_ica += ica ;
  _ion_ik += ik ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
double _dtsav = dt;
if (secondorder) { dt *= 0.5; }
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
  cao = _ion_cao;
  ica = _ion_ica;
  cai = _ion_cai;
  cai = _ion_cai;
  ek = _ion_ek;
 {  sparse_thread(&_thread[_spth2]._pvoid, 9, _slist2, _dlist2, _p, &t, dt, scheme1, _linmat2, _ppvar, _thread, _nt);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 9; ++_i) {
      _p[_slist2[_i]] += dt*_p[_dlist2[_i]];
    }}
 } {   states1(_p, _ppvar, _thread, _nt);
  }  _ion_cai = cai;
  }}
 dt = _dtsav;
}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(n) - _p;  _dlist1[0] = &(Dn) - _p;
 _slist2[0] = &(pumpca) - _p;  _dlist2[0] = &(Dpumpca) - _p;
 _slist2[1] = &(Bufer) - _p;  _dlist2[1] = &(DBufer) - _p;
 _slist2[2] = &(CaBufer) - _p;  _dlist2[2] = &(DCaBufer) - _p;
 _slist2[3] = &(Ca2HPCA) - _p;  _dlist2[3] = &(DCa2HPCA) - _p;
 _slist2[4] = &(CaHPCA) - _p;  _dlist2[4] = &(DCaHPCA) - _p;
 _slist2[5] = &(HPCA_m) - _p;  _dlist2[5] = &(DHPCA_m) - _p;
 _slist2[6] = &(HPCA) - _p;  _dlist2[6] = &(DHPCA) - _p;
 _slist2[7] = &(ca) - _p;  _dlist2[7] = &(Dca) - _p;
 _slist2[8] = &(pump) - _p;  _dlist2[8] = &(Dpump) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/arsentii/hippocalcin/HPCA-CA1/mechanism/hpca2.mod";
static const char* nmodl_file_text = 
  "NEURON {\n"
  "	SUFFIX hpca2\n"
  "	USEION ca READ cao, ica, cai  WRITE cai, ica\n"
  "	USEION k READ ek WRITE ik\n"
  "	RANGE HPCA_m_z, ca, ica_pmp, ica_basal, gbar, ik\n"
  "	GLOBAL Ra, cai0,  Rb, caix,q10, temp, tadj, vmin, vmax\n"
  "	THREADSAFE\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(molar) = (1/liter)\n"
  "	(mol) = (1)\n"
  "	(mM) = (millimolar)\n"
  "	(um) = (micron)\n"
  "	(mA) = (milliamp)\n"
  "	FARADAY = (faraday) (10000 coulomb)\n"
  "	PI = (pi) (1)\n"
  "	(pS) = (picosiemens)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	k1HPCA = 15 (/mM-ms)\n"
  "	k2HPCA = 0.01 (/ms)\n"
  "	k3HPCA = 16.67 (/mM-ms)\n"
  "	k4HPCA = 0.01 (/ms)\n"
  "	k_out = 0.002 (/ms) : uninsertion from the membrane\n"
  "	TotalHPCA = 0.03821 (mM)\n"
  "\n"
  "	D = 40 (um2/s)\n"
  "	\n"
  "	Bufer0 = 0.180 (mM) : initial concentration of the buffer\n"
  "	k1bufer = 10 (/mM-ms)\n"
  "	k2bufer = 1 (/ms)\n"
  "	\n"
  "	k1Pump = 1 (/mM-ms)\n"
  "	k2Pump = 0.0003 (/ms)\n"
  "	k3Pump = 1 (/ms)\n"
  "	k4Pump = 0.0003 (/mM-ms)\n"
  "	TotalPump = 1e-11 (mol/cm2)\n"
  "	cai0 = 100e-6 (mM) : initial [Ca2+]_i, 110 * 10^(-6) mM = 110 nM.\n"
  "	tau_d = 200 (ms)\n"
  "	delta = 0.1 (um)\n"
  "	\n"
  "	gbar = 600   	(pS/um2) : where does this come from? = 60 mS / cm2 = 0.06 S/cm2\n"
  "	caix = 1\n"
  "	Ra   = 0.01	(cm2/mol-ms)\n"
  "	Rb   = 0.02	(/ms)\n"
  "	temp = 36	(degC)\n"
  "	q10  = 2.3        : temperature adjustment parameter\n"
  "	vmin = -120	(mV)\n"
  "	vmax = 100	(mV)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    diam	    (um)\n"
  "    ica		    (mA/cm2)\n"
  "    drive_channels  (mM/ms)\n"
  "    cai		    (mM)\n"
  "    Vol		    (um2)\n"
  "    k_ins           (/ms) : insertion of the HPCA to the membrane\n"
  "    ica_balance	    (mA/cm2)\n"
  "    B0		    (mM)\n"
  "    HP0		    (mM)\n"
  "    cao		    (mM)\n"
  "    ica_pmp	    (mA/cm2)\n"
  "    ica_basal	    (mA/cm2)\n"
  "    ica_pmp_last    (mA/cm2) \n"
  "    parea (um)\n"
  "    a		    (/ms)\n"
  "    b		    (/ms)\n"
  "    ik		    (mA/cm2)\n"
  "    gk		    (pS/um2)\n"
  "    ek		    (mV)\n"
  "    ninf\n"
  "    ntau 	    (ms)	\n"
  "    tadj\n"
  "}\n"
  "\n"
  "CONSTANT { volo = 1e10 (um2) }\n"
  "\n"
  "STATE {\n"
  "	ca 		(mM)	    <1e-6>\n"
  "	HPCA  		(mM)\n"
  "	CaHPCA  	(mM)\n"
  "	Ca2HPCA 	(mM)\n"
  "	HPCA_m		(mol/cm2)   <1e-16>\n"
  "	\n"
  "	pump		(mol/cm2)   <1e-16>\n"
  "	pumpca		(mol/cm2)   <1e-16>\n"
  "	n\n"
  "	\n"
  "	HPCA_z          (mM)\n"
  "	CaHPCA_z        (mM)\n"
  "	Ca2HPCA_z       (mM)\n"
  "	HPCA_m_z        (mM)\n"
  "	HPCA_tot_z      (mM)\n"
  "	\n"
  "	Bufer           (mM)\n"
  "	CaBufer         (mM)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	cai = cai0\n"
  "	B0 =  Bufer0/(1 + (cai*k1bufer/k2bufer))\n"
  "	ca = cai\n"
  "	HPCA = TotalHPCA\n"
  "	Bufer = B0\n"
  "	CaBufer = Bufer0 - B0\n"
  "	parea = PI*diam\n"
  "	pump = TotalPump/(1 + (cai*k1Pump/k2Pump))\n"
  "	pumpca = TotalPump - pump\n"
  "	ica_pmp_last = 0\n"
  "	rates()\n"
  "	n = ninf\n"
  "}\n"
  "BREAKPOINT { \n"
  "	SOLVE scheme1 METHOD sparse\n"
  "	ica_pmp_last = ica_pmp\n"
  "	ica = ica_pmp \n"
  "	SOLVE states1 METHOD cnexp\n"
  "	gk = tadj*gbar*n\n"
  "	ik = (1e-4) * gk * (v - ek) : (1e-4) converts pS/um2 to S/cm2\n"
  "}\n"
  "\n"
  "\n"
  "DERIVATIVE states1 {\n"
  "	cai = ca  \n"
  "	rates()\n"
  "	n' =  (ninf-n)/ntau\n"
  "}\n"
  "\n"
  "\n"
  "LOCAL dsq, dsqvol, r\n"
  "LOCAL ica_basal \n"
  "\n"
  "KINETIC scheme1 {\n"
  "    r = diam/2\n"
  "    Vol = PI*r*r\n"
  "    ica_basal = 2*FARADAY*(k3Pump*TotalPump*cai0*(1e5)/(k2Pump/k1Pump))\n"
  "    k_ins = (1e-3)*(D * 0.1) / ( r^2 )\n"
  "\n"
  "    :multiplies right hand-sides of diff. equations by the volume\n"
  "    COMPARTMENT (1e10)*parea {pump pumpca HPCA_m}\n"
  "    COMPARTMENT volo {cao}\n"
  "    COMPARTMENT Vol {ca HPCA CaHPCA Ca2HPCA Bufer CaBufer}\n"
  "    \n"
  "    :kinetic equations for the Ca2+-ATPase\n"
  "    ~ ca + pump <-> pumpca (k1Pump*parea*(1e10), k2Pump*parea*(1e10))\n"
  "    ~ pumpca <-> pump + cao (k3Pump*parea*(1e10), k4Pump*parea*(1e10))\n"
  "    CONSERVE pump + pumpca = TotalPump * parea * (1e10)\n"
  "    ica_pmp = 2*FARADAY*(f_flux - b_flux)/parea\n"
  "\n"
  "    :all currents except pump\n"
  "    ~ ca << (-(ica - ica_basal - ica_pmp_last)*PI*diam/(2*FARADAY))\n"
  "\n"
  "    ~ ca + HPCA <-> CaHPCA (k1HPCA*Vol, k2HPCA*Vol)\n"
  "    ~ ca + CaHPCA <-> Ca2HPCA (k3HPCA*Vol, k4HPCA*Vol)\n"
  "    ~ ca + Bufer <-> CaBufer (k1bufer*Vol, k2bufer*Vol)\n"
  "    ~ Ca2HPCA <-> HPCA_m (k_ins*Vol, k_out*parea*(1e10)) \n"
  "\n"
  "    HPCA_z = HPCA*Vol\n"
  "    CaHPCA_z = CaHPCA*Vol\n"
  "    Ca2HPCA_z = Ca2HPCA*Vol\n"
  "    HPCA_m_z = HPCA_m*parea*(1e10)\n"
  "    HPCA_tot_z = HPCA_z + CaHPCA_z + Ca2HPCA_z + HPCA_m_z\n"
  "}\n"
  "\n"
  "\n"
  "PROCEDURE rates() {  \n"
  "	a = Ra * HPCA_m * parea*(1e11)\n"
  "	b = Rb\n"
  "	tadj = q10^((celsius - temp)/10)\n"
  "	ntau = 1/tadj/(a+b)\n"
  "	ninf = a/(a+b)\n"
  "}\n"
  "\n"
  "\n"
  "\n"
  ;
#endif

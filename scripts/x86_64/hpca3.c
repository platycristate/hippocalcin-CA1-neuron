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
 static void _difusfunc(ldifusfunc2_t, _NrnThread*);
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#include "nmodlmutex.h" 
#define nrn_init _nrn_init__hpca3
#define _nrn_initial _nrn_initial__hpca3
#define nrn_cur _nrn_cur__hpca3
#define _nrn_current _nrn_current__hpca3
#define nrn_jacob _nrn_jacob__hpca3
#define nrn_state _nrn_state__hpca3
#define _net_receive _net_receive__hpca3 
#define factors factors__hpca3 
#define rates rates__hpca3 
#define states states__hpca3 
#define scheme scheme__hpca3 
 
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
#define ca1 _p[1]
#define ca2 _p[2]
#define ca3 _p[3]
#define ca_avg _p[4]
#define ica_pmp _p[5]
#define ik _p[6]
#define ca (_p + 7)
#define HPCA (_p + 11)
#define CaHPCA (_p + 15)
#define Ca2HPCA (_p + 19)
#define HPCA_m _p[23]
#define pump _p[24]
#define pumpca _p[25]
#define n _p[26]
#define HPCA_z _p[27]
#define CaHPCA_z _p[28]
#define Ca2HPCA_z _p[29]
#define HPCA_m_z _p[30]
#define HPCA_tot_z _p[31]
#define Bufer (_p + 32)
#define CaBufer (_p + 36)
#define ica _p[40]
#define cai _p[41]
#define B0 _p[42]
#define HP0 _p[43]
#define cao _p[44]
#define ica_pmp_last _p[45]
#define parea _p[46]
#define a _p[47]
#define b _p[48]
#define gk _p[49]
#define ek _p[50]
#define ninf _p[51]
#define ntau _p[52]
#define Dca (_p + 53)
#define DHPCA (_p + 57)
#define DCaHPCA (_p + 61)
#define DCa2HPCA (_p + 65)
#define DHPCA_m _p[69]
#define Dpump _p[70]
#define Dpumpca _p[71]
#define Dn _p[72]
#define DHPCA_z _p[73]
#define DCaHPCA_z _p[74]
#define DCa2HPCA_z _p[75]
#define DHPCA_m_z _p[76]
#define DHPCA_tot_z _p[77]
#define DBufer (_p + 78)
#define DCaBufer (_p + 82)
#define v _p[86]
#define _g _p[87]
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
 static void _hoc_factors(void);
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
 "setdata_hpca3", _hoc_setdata,
 "factors_hpca3", _hoc_factors,
 "rates_hpca3", _hoc_rates,
 0, 0
};
 #define _zfactors_done _thread[2]._pval[0]
 #define _znexp _thread[2]._pval[1]
 #define _zdsq _thread[2]._pval[2]
 #define _zdsqvol _thread[2]._pval[3]
 #define _zfrat (_thread[2]._pval + 4)
 /* declare global and static user variables */
 static int _thread1data_inuse = 0;
static double _thread1data[5];
#define _gth 3
#define Bufer0 Bufer0_hpca3
 double Bufer0 = 20;
#define D_Bufer D_Bufer_hpca3
 double D_Bufer = 0.05;
#define Dhpca_m Dhpca_m_hpca3
 double Dhpca_m = 0.001;
#define Dca2hpca Dca2hpca_hpca3
 double Dca2hpca = 0.05;
#define Dcahpca Dcahpca_hpca3
 double Dcahpca = 0.05;
#define Dhpca Dhpca_hpca3
 double Dhpca = 0.05;
#define DCa DCa_hpca3
 double DCa = 0.22;
#define Rb Rb_hpca3
 double Rb = 0.02;
#define Ra Ra_hpca3
 double Ra = 0.01;
#define TotalPump TotalPump_hpca3
 double TotalPump = 1e-11;
#define TotalHPCA TotalHPCA_hpca3
 double TotalHPCA = 0.03821;
#define Volume_hpca3 (_thread1data + 0)
#define Volume (_thread[_gth]._pval + 0)
#define caix caix_hpca3
 double caix = 1;
#define cai0 cai0_hpca3
 double cai0 = 0.0001;
#define delta delta_hpca3
 double delta = 0.1;
#define k2Pump k2Pump_hpca3
 double k2Pump = 0.0003;
#define k1Pump k1Pump_hpca3
 double k1Pump = 1;
#define k2bufer k2bufer_hpca3
 double k2bufer = 1;
#define k1bufer k1bufer_hpca3
 double k1bufer = 10;
#define k8HPCA k8HPCA_hpca3
 double k8HPCA = 0.002;
#define k7HPCA k7HPCA_hpca3
 double k7HPCA = 0.01;
#define k4HPCA k4HPCA_hpca3
 double k4HPCA = 0.01;
#define k3HPCA k3HPCA_hpca3
 double k3HPCA = 40;
#define k2HPCA k2HPCA_hpca3
 double k2HPCA = 0.01;
#define k1HPCA k1HPCA_hpca3
 double k1HPCA = 40;
#define q10 q10_hpca3
 double q10 = 2.3;
#define tau_d tau_d_hpca3
 double tau_d = 200;
#define tadj_hpca3 _thread1data[4]
#define tadj _thread[_gth]._pval[4]
#define temp temp_hpca3
 double temp = 36;
#define vmax vmax_hpca3
 double vmax = 100;
#define vmin vmin_hpca3
 double vmin = -120;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "DCa_hpca3", "um2/ms",
 "Dhpca_hpca3", "um2/ms",
 "Dcahpca_hpca3", "um2/ms",
 "Dca2hpca_hpca3", "um2/ms",
 "Dhpca_m_hpca3", "um2/ms",
 "k1HPCA_hpca3", "/mM-ms",
 "k2HPCA_hpca3", "/ms",
 "k3HPCA_hpca3", "/mM-ms",
 "k4HPCA_hpca3", "/ms",
 "k7HPCA_hpca3", "/mM-ms",
 "k8HPCA_hpca3", "/ms",
 "TotalHPCA_hpca3", "mM",
 "D_Bufer_hpca3", "um2/ms",
 "Bufer0_hpca3", "mM",
 "k1bufer_hpca3", "/mM-ms",
 "k2bufer_hpca3", "/ms",
 "k1Pump_hpca3", "/mM-ms",
 "k2Pump_hpca3", "/ms",
 "TotalPump_hpca3", "mol/cm2",
 "cai0_hpca3", "mM",
 "tau_d_hpca3", "ms",
 "delta_hpca3", "um",
 "Ra_hpca3", "/ms",
 "Rb_hpca3", "/ms",
 "temp_hpca3", "degC",
 "vmin_hpca3", "mV",
 "vmax_hpca3", "mV",
 "Volume_hpca3", "um2",
 "gbar_hpca3", "pS/um2",
 "ca_hpca3", "mM",
 "HPCA_hpca3", "mM",
 "CaHPCA_hpca3", "mM",
 "Ca2HPCA_hpca3", "mM",
 "HPCA_m_hpca3", "mol/cm2",
 "pump_hpca3", "mol/cm2",
 "pumpca_hpca3", "mol/cm2",
 "HPCA_z_hpca3", "mM",
 "CaHPCA_z_hpca3", "mM",
 "Ca2HPCA_z_hpca3", "mM",
 "HPCA_m_z_hpca3", "mM",
 "HPCA_tot_z_hpca3", "mM",
 "Bufer_hpca3", "mM",
 "CaBufer_hpca3", "mM",
 "ca1_hpca3", "mM",
 "ca2_hpca3", "mM",
 "ca3_hpca3", "mM",
 "ca_avg_hpca3", "mM",
 "ica_pmp_hpca3", "mA/cm2",
 "ik_hpca3", "mA/cm2",
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
 "DCa_hpca3", &DCa_hpca3,
 "Dhpca_hpca3", &Dhpca_hpca3,
 "Dcahpca_hpca3", &Dcahpca_hpca3,
 "Dca2hpca_hpca3", &Dca2hpca_hpca3,
 "Dhpca_m_hpca3", &Dhpca_m_hpca3,
 "k1HPCA_hpca3", &k1HPCA_hpca3,
 "k2HPCA_hpca3", &k2HPCA_hpca3,
 "k3HPCA_hpca3", &k3HPCA_hpca3,
 "k4HPCA_hpca3", &k4HPCA_hpca3,
 "k7HPCA_hpca3", &k7HPCA_hpca3,
 "k8HPCA_hpca3", &k8HPCA_hpca3,
 "TotalHPCA_hpca3", &TotalHPCA_hpca3,
 "D_Bufer_hpca3", &D_Bufer_hpca3,
 "Bufer0_hpca3", &Bufer0_hpca3,
 "k1bufer_hpca3", &k1bufer_hpca3,
 "k2bufer_hpca3", &k2bufer_hpca3,
 "k1Pump_hpca3", &k1Pump_hpca3,
 "k2Pump_hpca3", &k2Pump_hpca3,
 "TotalPump_hpca3", &TotalPump_hpca3,
 "cai0_hpca3", &cai0_hpca3,
 "tau_d_hpca3", &tau_d_hpca3,
 "delta_hpca3", &delta_hpca3,
 "caix_hpca3", &caix_hpca3,
 "Ra_hpca3", &Ra_hpca3,
 "Rb_hpca3", &Rb_hpca3,
 "temp_hpca3", &temp_hpca3,
 "q10_hpca3", &q10_hpca3,
 "vmin_hpca3", &vmin_hpca3,
 "vmax_hpca3", &vmax_hpca3,
 "tadj_hpca3", &tadj_hpca3,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 "Volume_hpca3", Volume_hpca3, 4,
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
"hpca3",
 "gbar_hpca3",
 0,
 "ca1_hpca3",
 "ca2_hpca3",
 "ca3_hpca3",
 "ca_avg_hpca3",
 "ica_pmp_hpca3",
 "ik_hpca3",
 0,
 "ca_hpca3[4]",
 "HPCA_hpca3[4]",
 "CaHPCA_hpca3[4]",
 "Ca2HPCA_hpca3[4]",
 "HPCA_m_hpca3",
 "pump_hpca3",
 "pumpca_hpca3",
 "n_hpca3",
 "HPCA_z_hpca3",
 "CaHPCA_z_hpca3",
 "Ca2HPCA_z_hpca3",
 "HPCA_m_z_hpca3",
 "HPCA_tot_z_hpca3",
 "Bufer_hpca3[4]",
 "CaBufer_hpca3[4]",
 0,
 0};
 static Symbol* _morphology_sym;
 static Symbol* _ca_sym;
 static int _type_ica;
 static Symbol* _k_sym;
 static int _type_ik;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 88, _prop);
 	/*initialize range parameters*/
 	gbar = 600;
 	_prop->param = _p;
 	_prop->param_size = 88;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 9, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_morphology_sym);
 	_ppvar[8]._pval = &prop_ion->param[0]; /* diam */
 prop_ion = need_memb(_ca_sym);
  _type_ica = prop_ion->_type;
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_promote(prop_ion, 3, 0);
 	_ppvar[0]._pval = &prop_ion->param[2]; /* cao */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[2]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 	_ppvar[4]._pvoid = (void*)(&(prop_ion->dparam[0]._i)); /* iontype for ca */
 prop_ion = need_memb(_k_sym);
  _type_ik = prop_ion->_type;
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

 void _hpca3_reg() {
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
  hoc_register_prop_size(_mechtype, 88, 9);
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
 	hoc_register_ldifus1(_difusfunc);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 hpca3 /home/arsentii/hippocalcin/HPCA-CA1/mechanism/hpca3.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 9.64853;
 static double PI = 3.14159;
 static double volo = 1e10;
 /*Top LOCAL _zfactors_done , _znexp */
 /*Top LOCAL _zdsq , _zdsqvol */
 /*Top LOCAL _zfrat [ 4 ] */
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int factors(_threadargsproto_);
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
 static int _slist2[27], _dlist2[27]; static double *_temp2;
 static int scheme();
 static int _slist1[1], _dlist1[1];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   cai = ca [ 0 ] ;
   ca1 = ca [ 1 ] ;
   ca2 = ca [ 2 ] ;
   ca3 = ca [ 3 ] ;
   rates ( _threadargs_ ) ;
   Dn = ( ninf - n ) / ntau ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 cai = ca [ 0 ] ;
 ca1 = ca [ 1 ] ;
 ca2 = ca [ 2 ] ;
 ca3 = ca [ 3 ] ;
 rates ( _threadargs_ ) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ntau )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   cai = ca [ 0 ] ;
   ca1 = ca [ 1 ] ;
   ca2 = ca [ 2 ] ;
   ca3 = ca [ 3 ] ;
   rates ( _threadargs_ ) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ntau)))*(- ( ( ( ninf ) ) / ntau ) / ( ( ( ( - 1.0 ) ) ) / ntau ) - n) ;
   }
  return 0;
}
 
static int scheme (void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=1;_i<27;_i++){
  	_RHS2(_i) = -_dt1*(_p[_slist2[_i]] - _p[_dlist2[_i]]);
	_MATELM2(_i, _i) = _dt1;
      
}  
_RHS2(17) *= ( ( 1e10 ) * parea) ;
_MATELM2(17, 17) *= ( ( 1e10 ) * parea); 
_RHS2(26) *= ( ( 1e10 ) * parea) ;
_MATELM2(26, 26) *= ( ( 1e10 ) * parea);  
for (_i=0; _i < 4; _i++) {
  	_RHS2(_i + 1) *= ( _zdsq * Volume [ ((int) _i ) ]) ;
_MATELM2(_i + 1, _i + 1) *= ( _zdsq * Volume [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS2(_i + 5) *= ( _zdsq * Volume [ ((int) _i ) ]) ;
_MATELM2(_i + 5, _i + 5) *= ( _zdsq * Volume [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS2(_i + 9) *= ( _zdsq * Volume [ ((int) _i ) ]) ;
_MATELM2(_i + 9, _i + 9) *= ( _zdsq * Volume [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS2(_i + 13) *= ( _zdsq * Volume [ ((int) _i ) ]) ;
_MATELM2(_i + 13, _i + 13) *= ( _zdsq * Volume [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS2(_i + 18) *= ( _zdsq * Volume [ ((int) _i ) ]) ;
_MATELM2(_i + 18, _i + 18) *= ( _zdsq * Volume [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS2(_i + 22) *= ( _zdsq * Volume [ ((int) _i ) ]) ;
_MATELM2(_i + 22, _i + 22) *= ( _zdsq * Volume [ ((int) _i ) ]);  } }
 _zdsq = diam * diam ;
   /* COMPARTMENT ( 1e10 ) * parea {
     pump pumpca HPCA_m }
   */
 /* COMPARTMENT volo {
     }
   */
 /* COMPARTMENT _li , _zdsq * Volume [ ((int) _i ) ] {
     ca HPCA CaHPCA Ca2HPCA Bufer CaBufer }
   */
 /* LONGITUDINAL_DIFFUSION _li , DCa * _zdsq * Volume [ ((int) _i ) ] {
     ca }
   */
 /* LONGITUDINAL_DIFFUSION _li , Dhpca * _zdsq * Volume [ ((int) _i ) ] {
     HPCA }
   */
 /* LONGITUDINAL_DIFFUSION _li , Dcahpca * _zdsq * Volume [ ((int) _i ) ] {
     CaHPCA }
   */
 /* LONGITUDINAL_DIFFUSION _li , Dca2hpca * _zdsq * Volume [ ((int) _i ) ] {
     Ca2HPCA }
   */
 /* LONGITUDINAL_DIFFUSION Dhpca_m * parea * ( 1e10 ) {
     HPCA_m }
   */
 /* LONGITUDINAL_DIFFUSION _li , D_Bufer * _zdsq * Volume [ ((int) _i ) ] {
     Bufer }
   */
 /* ~ ca [ 0 ] + pump <-> pumpca ( k1Pump * parea * ( 1e10 ) , k2Pump * parea * ( 1e10 ) )*/
 f_flux =  k1Pump * parea * ( 1e10 ) * pump * ca [ 0] ;
 b_flux =  k2Pump * parea * ( 1e10 ) * pumpca ;
 _RHS2( 26) -= (f_flux - b_flux);
 _RHS2( 22 +  0) -= (f_flux - b_flux);
 
 _term =  k1Pump * parea * ( 1e10 ) * ca [ 0] ;
 _MATELM2( 26 ,26)  += _term;
 _MATELM2( 22 +  0 ,26)  += _term;
 _term =  k1Pump * parea * ( 1e10 ) * pump ;
 _MATELM2( 26 ,22 +  0)  += _term;
 _MATELM2( 22 +  0 ,22 +  0)  += _term;
 _term =  k2Pump * parea * ( 1e10 ) ;
 _MATELM2( 26 ,0)  -= _term;
 _MATELM2( 22 +  0 ,0)  -= _term;
 /*REACTION*/
  /* ~ pumpca <-> pump + cao ( k1Pump * parea * ( 1e10 ) , k2Pump * parea * ( 1e10 ) )*/
 f_flux =  k1Pump * parea * ( 1e10 ) * pumpca ;
 b_flux =  k2Pump * parea * ( 1e10 ) * cao * pump ;
 _RHS2( 26) += (f_flux - b_flux);
 
 _term =  k1Pump * parea * ( 1e10 ) ;
 _MATELM2( 26 ,0)  -= _term;
 _term =  k2Pump * parea * ( 1e10 ) * cao ;
 _MATELM2( 26 ,26)  += _term;
 /*REACTION*/
   /* pump + pumpca = TotalPump * parea * ( 1e10 ) */
 _RHS2(0) =  TotalPump * parea * ( 1e10 );
 _MATELM2(0, 0) = 1 * ( ( 1e10 ) * parea);
 _RHS2(0) -= pumpca * ( ( 1e10 ) * parea) ;
 _MATELM2(0, 26) = 1 * ( ( 1e10 ) * parea);
 _RHS2(0) -= pump * ( ( 1e10 ) * parea) ;
 /*CONSERVATION*/
 ica_pmp = 2.0 * FARADAY * ( f_flux - b_flux ) / parea ;
   /* ~ ca [ 0 ] < < ( - ( ica - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) )*/
 f_flux = b_flux = 0.;
 _RHS2( 22 +  0) += (b_flux =   ( - ( ica - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) ) );
 /*FLUX*/
  {int  _li ;for ( _li = 0 ; _li <= 4 - 2 ; _li ++ ) {
     /* ~ ca [ _li ] <-> ca [ _li + 1 ] ( DCa * _zfrat [ _li + 1 ] , DCa * _zfrat [ _li + 1 ] )*/
 f_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li] ;
 b_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li + 1] ;
 _RHS2( 22 +  _li) -= (f_flux - b_flux);
 _RHS2( 22 +  _li + 1) += (f_flux - b_flux);
 
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM2( 22 +  _li ,22 +  _li)  += _term;
 _MATELM2( 22 +  _li + 1 ,22 +  _li)  -= _term;
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM2( 22 +  _li ,22 +  _li + 1)  -= _term;
 _MATELM2( 22 +  _li + 1 ,22 +  _li + 1)  += _term;
 /*REACTION*/
  /* ~ HPCA [ _li ] <-> HPCA [ _li + 1 ] ( Dhpca * _zfrat [ _li + 1 ] , Dhpca * _zfrat [ _li + 1 ] )*/
 f_flux =  Dhpca * _zfrat [ _li + 1 ] * HPCA [ _li] ;
 b_flux =  Dhpca * _zfrat [ _li + 1 ] * HPCA [ _li + 1] ;
 _RHS2( 18 +  _li) -= (f_flux - b_flux);
 _RHS2( 18 +  _li + 1) += (f_flux - b_flux);
 
 _term =  Dhpca * _zfrat [ _li + 1 ] ;
 _MATELM2( 18 +  _li ,18 +  _li)  += _term;
 _MATELM2( 18 +  _li + 1 ,18 +  _li)  -= _term;
 _term =  Dhpca * _zfrat [ _li + 1 ] ;
 _MATELM2( 18 +  _li ,18 +  _li + 1)  -= _term;
 _MATELM2( 18 +  _li + 1 ,18 +  _li + 1)  += _term;
 /*REACTION*/
  /* ~ CaHPCA [ _li ] <-> CaHPCA [ _li + 1 ] ( Dcahpca * _zfrat [ _li + 1 ] , Dcahpca * _zfrat [ _li + 1 ] )*/
 f_flux =  Dcahpca * _zfrat [ _li + 1 ] * CaHPCA [ _li] ;
 b_flux =  Dcahpca * _zfrat [ _li + 1 ] * CaHPCA [ _li + 1] ;
 _RHS2( 13 +  _li) -= (f_flux - b_flux);
 _RHS2( 13 +  _li + 1) += (f_flux - b_flux);
 
 _term =  Dcahpca * _zfrat [ _li + 1 ] ;
 _MATELM2( 13 +  _li ,13 +  _li)  += _term;
 _MATELM2( 13 +  _li + 1 ,13 +  _li)  -= _term;
 _term =  Dcahpca * _zfrat [ _li + 1 ] ;
 _MATELM2( 13 +  _li ,13 +  _li + 1)  -= _term;
 _MATELM2( 13 +  _li + 1 ,13 +  _li + 1)  += _term;
 /*REACTION*/
  /* ~ Ca2HPCA [ _li ] <-> Ca2HPCA [ _li + 1 ] ( Dca2hpca * _zfrat [ _li + 1 ] , Dca2hpca * _zfrat [ _li + 1 ] )*/
 f_flux =  Dca2hpca * _zfrat [ _li + 1 ] * Ca2HPCA [ _li] ;
 b_flux =  Dca2hpca * _zfrat [ _li + 1 ] * Ca2HPCA [ _li + 1] ;
 _RHS2( 9 +  _li) -= (f_flux - b_flux);
 _RHS2( 9 +  _li + 1) += (f_flux - b_flux);
 
 _term =  Dca2hpca * _zfrat [ _li + 1 ] ;
 _MATELM2( 9 +  _li ,9 +  _li)  += _term;
 _MATELM2( 9 +  _li + 1 ,9 +  _li)  -= _term;
 _term =  Dca2hpca * _zfrat [ _li + 1 ] ;
 _MATELM2( 9 +  _li ,9 +  _li + 1)  -= _term;
 _MATELM2( 9 +  _li + 1 ,9 +  _li + 1)  += _term;
 /*REACTION*/
  /* ~ Bufer [ _li ] <-> Bufer [ _li + 1 ] ( D_Bufer * _zfrat [ _li + 1 ] , D_Bufer * _zfrat [ _li + 1 ] )*/
 f_flux =  D_Bufer * _zfrat [ _li + 1 ] * Bufer [ _li] ;
 b_flux =  D_Bufer * _zfrat [ _li + 1 ] * Bufer [ _li + 1] ;
 _RHS2( 1 +  _li) -= (f_flux - b_flux);
 _RHS2( 1 +  _li + 1) += (f_flux - b_flux);
 
 _term =  D_Bufer * _zfrat [ _li + 1 ] ;
 _MATELM2( 1 +  _li ,1 +  _li)  += _term;
 _MATELM2( 1 +  _li + 1 ,1 +  _li)  -= _term;
 _term =  D_Bufer * _zfrat [ _li + 1 ] ;
 _MATELM2( 1 +  _li ,1 +  _li + 1)  -= _term;
 _MATELM2( 1 +  _li + 1 ,1 +  _li + 1)  += _term;
 /*REACTION*/
  } }
   {int  _li ;for ( _li = 0 ; _li <= 4 - 1 ; _li ++ ) {
     _zdsqvol = _zdsq * Volume [ _li ] ;
     /* ~ ca [ _li ] + HPCA [ _li ] <-> CaHPCA [ _li ] ( k1HPCA * _zdsqvol , k2HPCA * _zdsqvol )*/
 f_flux =  k1HPCA * _zdsqvol * HPCA [ _li] * ca [ _li] ;
 b_flux =  k2HPCA * _zdsqvol * CaHPCA [ _li] ;
 _RHS2( 18 +  _li) -= (f_flux - b_flux);
 _RHS2( 22 +  _li) -= (f_flux - b_flux);
 _RHS2( 13 +  _li) += (f_flux - b_flux);
 
 _term =  k1HPCA * _zdsqvol * ca [ _li] ;
 _MATELM2( 18 +  _li ,18 +  _li)  += _term;
 _MATELM2( 22 +  _li ,18 +  _li)  += _term;
 _MATELM2( 13 +  _li ,18 +  _li)  -= _term;
 _term =  k1HPCA * _zdsqvol * HPCA [ _li] ;
 _MATELM2( 18 +  _li ,22 +  _li)  += _term;
 _MATELM2( 22 +  _li ,22 +  _li)  += _term;
 _MATELM2( 13 +  _li ,22 +  _li)  -= _term;
 _term =  k2HPCA * _zdsqvol ;
 _MATELM2( 18 +  _li ,13 +  _li)  -= _term;
 _MATELM2( 22 +  _li ,13 +  _li)  -= _term;
 _MATELM2( 13 +  _li ,13 +  _li)  += _term;
 /*REACTION*/
  /* ~ ca [ _li ] + CaHPCA [ _li ] <-> Ca2HPCA [ _li ] ( k3HPCA * _zdsqvol , k4HPCA * _zdsqvol )*/
 f_flux =  k3HPCA * _zdsqvol * CaHPCA [ _li] * ca [ _li] ;
 b_flux =  k4HPCA * _zdsqvol * Ca2HPCA [ _li] ;
 _RHS2( 13 +  _li) -= (f_flux - b_flux);
 _RHS2( 22 +  _li) -= (f_flux - b_flux);
 _RHS2( 9 +  _li) += (f_flux - b_flux);
 
 _term =  k3HPCA * _zdsqvol * ca [ _li] ;
 _MATELM2( 13 +  _li ,13 +  _li)  += _term;
 _MATELM2( 22 +  _li ,13 +  _li)  += _term;
 _MATELM2( 9 +  _li ,13 +  _li)  -= _term;
 _term =  k3HPCA * _zdsqvol * CaHPCA [ _li] ;
 _MATELM2( 13 +  _li ,22 +  _li)  += _term;
 _MATELM2( 22 +  _li ,22 +  _li)  += _term;
 _MATELM2( 9 +  _li ,22 +  _li)  -= _term;
 _term =  k4HPCA * _zdsqvol ;
 _MATELM2( 13 +  _li ,9 +  _li)  -= _term;
 _MATELM2( 22 +  _li ,9 +  _li)  -= _term;
 _MATELM2( 9 +  _li ,9 +  _li)  += _term;
 /*REACTION*/
  /* ~ ca [ _li ] + Bufer [ _li ] <-> CaBufer [ _li ] ( k1bufer * _zdsqvol , k2bufer * _zdsqvol )*/
 f_flux =  k1bufer * _zdsqvol * Bufer [ _li] * ca [ _li] ;
 b_flux =  k2bufer * _zdsqvol * CaBufer [ _li] ;
 _RHS2( 1 +  _li) -= (f_flux - b_flux);
 _RHS2( 22 +  _li) -= (f_flux - b_flux);
 _RHS2( 5 +  _li) += (f_flux - b_flux);
 
 _term =  k1bufer * _zdsqvol * ca [ _li] ;
 _MATELM2( 1 +  _li ,1 +  _li)  += _term;
 _MATELM2( 22 +  _li ,1 +  _li)  += _term;
 _MATELM2( 5 +  _li ,1 +  _li)  -= _term;
 _term =  k1bufer * _zdsqvol * Bufer [ _li] ;
 _MATELM2( 1 +  _li ,22 +  _li)  += _term;
 _MATELM2( 22 +  _li ,22 +  _li)  += _term;
 _MATELM2( 5 +  _li ,22 +  _li)  -= _term;
 _term =  k2bufer * _zdsqvol ;
 _MATELM2( 1 +  _li ,5 +  _li)  -= _term;
 _MATELM2( 22 +  _li ,5 +  _li)  -= _term;
 _MATELM2( 5 +  _li ,5 +  _li)  += _term;
 /*REACTION*/
  } }
   /* ~ Ca2HPCA [ 0 ] <-> HPCA_m ( k7HPCA * _zdsq * Volume [ 0 ] , k8HPCA * parea * ( 1e10 ) )*/
 f_flux =  k7HPCA * _zdsq * Volume [ 0 ] * Ca2HPCA [ 0] ;
 b_flux =  k8HPCA * parea * ( 1e10 ) * HPCA_m ;
 _RHS2( 9 +  0) -= (f_flux - b_flux);
 _RHS2( 17) += (f_flux - b_flux);
 
 _term =  k7HPCA * _zdsq * Volume [ 0 ] ;
 _MATELM2( 9 +  0 ,9 +  0)  += _term;
 _MATELM2( 17 ,9 +  0)  -= _term;
 _term =  k8HPCA * parea * ( 1e10 ) ;
 _MATELM2( 9 +  0 ,17)  -= _term;
 _MATELM2( 17 ,17)  += _term;
 /*REACTION*/
  HPCA_z = _zdsq * ( HPCA [ 0 ] * Volume [ 0 ] + HPCA [ 1 ] * Volume [ 1 ] + HPCA [ 2 ] * Volume [ 2 ] + HPCA [ 3 ] * Volume [ 3 ] ) ;
   CaHPCA_z = _zdsq * ( CaHPCA [ 0 ] * Volume [ 0 ] + CaHPCA [ 1 ] * Volume [ 1 ] + CaHPCA [ 2 ] * Volume [ 2 ] + CaHPCA [ 3 ] * Volume [ 3 ] ) ;
   Ca2HPCA_z = _zdsq * ( Ca2HPCA [ 0 ] * Volume [ 0 ] + Ca2HPCA [ 1 ] * Volume [ 1 ] + Ca2HPCA [ 2 ] * Volume [ 2 ] + Ca2HPCA [ 3 ] * Volume [ 3 ] ) ;
   HPCA_m_z = HPCA_m * parea * ( 1e10 ) ;
   HPCA_tot_z = HPCA_z + CaHPCA_z + Ca2HPCA_z + HPCA_m_z ;
     } return _reset;
 }
 
static int  rates ( _threadargsproto_ ) {
   a = Ra * HPCA_m ;
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
 
static int  factors ( _threadargsproto_ ) {
   double _lr , _ldr2 ;
 _lr = 1.0 / 2.0 ;
   _ldr2 = _lr / ( 4.0 - 1.0 ) / 2.0 ;
   Volume [ 0 ] = 0.0 ;
   _zfrat [ 0 ] = 2.0 * _lr ;
   {int  _li ;for ( _li = 0 ; _li <= 4 - 2 ; _li ++ ) {
     Volume [ _li ] = Volume [ _li ] + PI * ( _lr - _ldr2 / 2.0 ) * 2.0 * _ldr2 ;
     _lr = _lr - _ldr2 ;
     _zfrat [ _li + 1 ] = 2.0 * PI * _lr / ( 2.0 * _ldr2 ) ;
     _lr = _lr - _ldr2 ;
     Volume [ _li + 1 ] = PI * ( _lr + _ldr2 / 2.0 ) * 2.0 * _ldr2 ;
     } }
    return 0; }
 
static void _hoc_factors(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 factors ( _p, _ppvar, _thread, _nt );
 hoc_retpushx(_r);
}
 
/*CVODE ode begin*/
 static int _ode_spec2(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<27;_i++) _p[_dlist2[_i]] = 0.0;}
 _zdsq = diam * diam ;
 /* COMPARTMENT ( 1e10 ) * parea {
   pump pumpca HPCA_m }
 */
 /* COMPARTMENT volo {
   }
 */
 /* COMPARTMENT _li , _zdsq * Volume [ ((int) _i ) ] {
   ca HPCA CaHPCA Ca2HPCA Bufer CaBufer }
 */
 /* LONGITUDINAL_DIFFUSION _li , DCa * _zdsq * Volume [ ((int) _i ) ] {
   ca }
 */
 /* LONGITUDINAL_DIFFUSION _li , Dhpca * _zdsq * Volume [ ((int) _i ) ] {
   HPCA }
 */
 /* LONGITUDINAL_DIFFUSION _li , Dcahpca * _zdsq * Volume [ ((int) _i ) ] {
   CaHPCA }
 */
 /* LONGITUDINAL_DIFFUSION _li , Dca2hpca * _zdsq * Volume [ ((int) _i ) ] {
   Ca2HPCA }
 */
 /* LONGITUDINAL_DIFFUSION Dhpca_m * parea * ( 1e10 ) {
   HPCA_m }
 */
 /* LONGITUDINAL_DIFFUSION _li , D_Bufer * _zdsq * Volume [ ((int) _i ) ] {
   Bufer }
 */
 /* ~ ca [ 0 ] + pump <-> pumpca ( k1Pump * parea * ( 1e10 ) , k2Pump * parea * ( 1e10 ) )*/
 f_flux =  k1Pump * parea * ( 1e10 ) * pump * ca [ 0] ;
 b_flux =  k2Pump * parea * ( 1e10 ) * pumpca ;
 Dpump -= (f_flux - b_flux);
 Dca [ 0] -= (f_flux - b_flux);
 Dpumpca += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ pumpca <-> pump + cao ( k1Pump * parea * ( 1e10 ) , k2Pump * parea * ( 1e10 ) )*/
 f_flux =  k1Pump * parea * ( 1e10 ) * pumpca ;
 b_flux =  k2Pump * parea * ( 1e10 ) * cao * pump ;
 Dpumpca -= (f_flux - b_flux);
 Dpump += (f_flux - b_flux);
 
 /*REACTION*/
   /* pump + pumpca = TotalPump * parea * ( 1e10 ) */
 /*CONSERVATION*/
 ica_pmp = 2.0 * FARADAY * ( f_flux - b_flux ) / parea ;
 /* ~ ca [ 0 ] < < ( - ( ica - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) )*/
 f_flux = b_flux = 0.;
 Dca [ 0] += (b_flux =   ( - ( ica - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) ) );
 /*FLUX*/
  {int  _li ;for ( _li = 0 ; _li <= 4 - 2 ; _li ++ ) {
   /* ~ ca [ _li ] <-> ca [ _li + 1 ] ( DCa * _zfrat [ _li + 1 ] , DCa * _zfrat [ _li + 1 ] )*/
 f_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li] ;
 b_flux =  DCa * _zfrat [ _li + 1 ] * ca [ _li + 1] ;
 Dca [ _li] -= (f_flux - b_flux);
 Dca [ _li + 1] += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ HPCA [ _li ] <-> HPCA [ _li + 1 ] ( Dhpca * _zfrat [ _li + 1 ] , Dhpca * _zfrat [ _li + 1 ] )*/
 f_flux =  Dhpca * _zfrat [ _li + 1 ] * HPCA [ _li] ;
 b_flux =  Dhpca * _zfrat [ _li + 1 ] * HPCA [ _li + 1] ;
 DHPCA [ _li] -= (f_flux - b_flux);
 DHPCA [ _li + 1] += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ CaHPCA [ _li ] <-> CaHPCA [ _li + 1 ] ( Dcahpca * _zfrat [ _li + 1 ] , Dcahpca * _zfrat [ _li + 1 ] )*/
 f_flux =  Dcahpca * _zfrat [ _li + 1 ] * CaHPCA [ _li] ;
 b_flux =  Dcahpca * _zfrat [ _li + 1 ] * CaHPCA [ _li + 1] ;
 DCaHPCA [ _li] -= (f_flux - b_flux);
 DCaHPCA [ _li + 1] += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ Ca2HPCA [ _li ] <-> Ca2HPCA [ _li + 1 ] ( Dca2hpca * _zfrat [ _li + 1 ] , Dca2hpca * _zfrat [ _li + 1 ] )*/
 f_flux =  Dca2hpca * _zfrat [ _li + 1 ] * Ca2HPCA [ _li] ;
 b_flux =  Dca2hpca * _zfrat [ _li + 1 ] * Ca2HPCA [ _li + 1] ;
 DCa2HPCA [ _li] -= (f_flux - b_flux);
 DCa2HPCA [ _li + 1] += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ Bufer [ _li ] <-> Bufer [ _li + 1 ] ( D_Bufer * _zfrat [ _li + 1 ] , D_Bufer * _zfrat [ _li + 1 ] )*/
 f_flux =  D_Bufer * _zfrat [ _li + 1 ] * Bufer [ _li] ;
 b_flux =  D_Bufer * _zfrat [ _li + 1 ] * Bufer [ _li + 1] ;
 DBufer [ _li] -= (f_flux - b_flux);
 DBufer [ _li + 1] += (f_flux - b_flux);
 
 /*REACTION*/
  } }
 {int  _li ;for ( _li = 0 ; _li <= 4 - 1 ; _li ++ ) {
   _zdsqvol = _zdsq * Volume [ _li ] ;
   /* ~ ca [ _li ] + HPCA [ _li ] <-> CaHPCA [ _li ] ( k1HPCA * _zdsqvol , k2HPCA * _zdsqvol )*/
 f_flux =  k1HPCA * _zdsqvol * HPCA [ _li] * ca [ _li] ;
 b_flux =  k2HPCA * _zdsqvol * CaHPCA [ _li] ;
 DHPCA [ _li] -= (f_flux - b_flux);
 Dca [ _li] -= (f_flux - b_flux);
 DCaHPCA [ _li] += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca [ _li ] + CaHPCA [ _li ] <-> Ca2HPCA [ _li ] ( k3HPCA * _zdsqvol , k4HPCA * _zdsqvol )*/
 f_flux =  k3HPCA * _zdsqvol * CaHPCA [ _li] * ca [ _li] ;
 b_flux =  k4HPCA * _zdsqvol * Ca2HPCA [ _li] ;
 DCaHPCA [ _li] -= (f_flux - b_flux);
 Dca [ _li] -= (f_flux - b_flux);
 DCa2HPCA [ _li] += (f_flux - b_flux);
 
 /*REACTION*/
  /* ~ ca [ _li ] + Bufer [ _li ] <-> CaBufer [ _li ] ( k1bufer * _zdsqvol , k2bufer * _zdsqvol )*/
 f_flux =  k1bufer * _zdsqvol * Bufer [ _li] * ca [ _li] ;
 b_flux =  k2bufer * _zdsqvol * CaBufer [ _li] ;
 DBufer [ _li] -= (f_flux - b_flux);
 Dca [ _li] -= (f_flux - b_flux);
 DCaBufer [ _li] += (f_flux - b_flux);
 
 /*REACTION*/
  } }
 /* ~ Ca2HPCA [ 0 ] <-> HPCA_m ( k7HPCA * _zdsq * Volume [ 0 ] , k8HPCA * parea * ( 1e10 ) )*/
 f_flux =  k7HPCA * _zdsq * Volume [ 0 ] * Ca2HPCA [ 0] ;
 b_flux =  k8HPCA * parea * ( 1e10 ) * HPCA_m ;
 DCa2HPCA [ 0] -= (f_flux - b_flux);
 DHPCA_m += (f_flux - b_flux);
 
 /*REACTION*/
  HPCA_z = _zdsq * ( HPCA [ 0 ] * Volume [ 0 ] + HPCA [ 1 ] * Volume [ 1 ] + HPCA [ 2 ] * Volume [ 2 ] + HPCA [ 3 ] * Volume [ 3 ] ) ;
 CaHPCA_z = _zdsq * ( CaHPCA [ 0 ] * Volume [ 0 ] + CaHPCA [ 1 ] * Volume [ 1 ] + CaHPCA [ 2 ] * Volume [ 2 ] + CaHPCA [ 3 ] * Volume [ 3 ] ) ;
 Ca2HPCA_z = _zdsq * ( Ca2HPCA [ 0 ] * Volume [ 0 ] + Ca2HPCA [ 1 ] * Volume [ 1 ] + Ca2HPCA [ 2 ] * Volume [ 2 ] + Ca2HPCA [ 3 ] * Volume [ 3 ] ) ;
 HPCA_m_z = HPCA_m * parea * ( 1e10 ) ;
 HPCA_tot_z = HPCA_z + CaHPCA_z + Ca2HPCA_z + HPCA_m_z ;
 _p[_dlist2[0]] /= ( ( 1e10 ) * parea);
 for (_i=0; _i < 4; _i++) { _p[_dlist2[_i + 1]] /= ( _zdsq * Volume [ ((int) _i ) ]);}
 for (_i=0; _i < 4; _i++) { _p[_dlist2[_i + 5]] /= ( _zdsq * Volume [ ((int) _i ) ]);}
 for (_i=0; _i < 4; _i++) { _p[_dlist2[_i + 9]] /= ( _zdsq * Volume [ ((int) _i ) ]);}
 for (_i=0; _i < 4; _i++) { _p[_dlist2[_i + 13]] /= ( _zdsq * Volume [ ((int) _i ) ]);}
 _p[_dlist2[17]] /= ( ( 1e10 ) * parea);
 for (_i=0; _i < 4; _i++) { _p[_dlist2[_i + 18]] /= ( _zdsq * Volume [ ((int) _i ) ]);}
 for (_i=0; _i < 4; _i++) { _p[_dlist2[_i + 22]] /= ( _zdsq * Volume [ ((int) _i ) ]);}
 _p[_dlist2[26]] /= ( ( 1e10 ) * parea);
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol2(void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<27;_i++){
  	_RHS2(_i) = _dt1*(_p[_dlist2[_i]]);
	_MATELM2(_i, _i) = _dt1;
      
}  
_RHS2(0) *= ( ( 1e10 ) * parea) ;
_MATELM2(0, 0) *= ( ( 1e10 ) * parea); 
_RHS2(17) *= ( ( 1e10 ) * parea) ;
_MATELM2(17, 17) *= ( ( 1e10 ) * parea); 
_RHS2(26) *= ( ( 1e10 ) * parea) ;
_MATELM2(26, 26) *= ( ( 1e10 ) * parea);  
for (_i=0; _i < 4; _i++) {
  	_RHS2(_i + 1) *= ( _zdsq * Volume [ ((int) _i ) ]) ;
_MATELM2(_i + 1, _i + 1) *= ( _zdsq * Volume [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS2(_i + 5) *= ( _zdsq * Volume [ ((int) _i ) ]) ;
_MATELM2(_i + 5, _i + 5) *= ( _zdsq * Volume [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS2(_i + 9) *= ( _zdsq * Volume [ ((int) _i ) ]) ;
_MATELM2(_i + 9, _i + 9) *= ( _zdsq * Volume [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS2(_i + 13) *= ( _zdsq * Volume [ ((int) _i ) ]) ;
_MATELM2(_i + 13, _i + 13) *= ( _zdsq * Volume [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS2(_i + 18) *= ( _zdsq * Volume [ ((int) _i ) ]) ;
_MATELM2(_i + 18, _i + 18) *= ( _zdsq * Volume [ ((int) _i ) ]);  } 
for (_i=0; _i < 4; _i++) {
  	_RHS2(_i + 22) *= ( _zdsq * Volume [ ((int) _i ) ]) ;
_MATELM2(_i + 22, _i + 22) *= ( _zdsq * Volume [ ((int) _i ) ]);  } }
 _zdsq = diam * diam ;
 /* COMPARTMENT ( 1e10 ) * parea {
 pump pumpca HPCA_m }
 */
 /* COMPARTMENT volo {
 }
 */
 /* COMPARTMENT _li , _zdsq * Volume [ ((int) _i ) ] {
 ca HPCA CaHPCA Ca2HPCA Bufer CaBufer }
 */
 /* LONGITUDINAL_DIFFUSION _li , DCa * _zdsq * Volume [ ((int) _i ) ] {
 ca }
 */
 /* LONGITUDINAL_DIFFUSION _li , Dhpca * _zdsq * Volume [ ((int) _i ) ] {
 HPCA }
 */
 /* LONGITUDINAL_DIFFUSION _li , Dcahpca * _zdsq * Volume [ ((int) _i ) ] {
 CaHPCA }
 */
 /* LONGITUDINAL_DIFFUSION _li , Dca2hpca * _zdsq * Volume [ ((int) _i ) ] {
 Ca2HPCA }
 */
 /* LONGITUDINAL_DIFFUSION Dhpca_m * parea * ( 1e10 ) {
 HPCA_m }
 */
 /* LONGITUDINAL_DIFFUSION _li , D_Bufer * _zdsq * Volume [ ((int) _i ) ] {
 Bufer }
 */
 /* ~ ca [ 0 ] + pump <-> pumpca ( k1Pump * parea * ( 1e10 ) , k2Pump * parea * ( 1e10 ) )*/
 _term =  k1Pump * parea * ( 1e10 ) * ca [ 0] ;
 _MATELM2( 26 ,26)  += _term;
 _MATELM2( 22 +  0 ,26)  += _term;
 _MATELM2( 0 ,26)  -= _term;
 _term =  k1Pump * parea * ( 1e10 ) * pump ;
 _MATELM2( 26 ,22 +  0)  += _term;
 _MATELM2( 22 +  0 ,22 +  0)  += _term;
 _MATELM2( 0 ,22 +  0)  -= _term;
 _term =  k2Pump * parea * ( 1e10 ) ;
 _MATELM2( 26 ,0)  -= _term;
 _MATELM2( 22 +  0 ,0)  -= _term;
 _MATELM2( 0 ,0)  += _term;
 /*REACTION*/
  /* ~ pumpca <-> pump + cao ( k1Pump * parea * ( 1e10 ) , k2Pump * parea * ( 1e10 ) )*/
 _term =  k1Pump * parea * ( 1e10 ) ;
 _MATELM2( 0 ,0)  += _term;
 _MATELM2( 26 ,0)  -= _term;
 _term =  k2Pump * parea * ( 1e10 ) * cao ;
 _MATELM2( 0 ,26)  -= _term;
 _MATELM2( 26 ,26)  += _term;
 /* ~ ca [ 0 ] < < ( - ( ica - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) )*/
 /*FLUX*/
  {int  _li ;for ( _li = 0 ; _li <= 4 - 2 ; _li ++ ) {
 /* ~ ca [ _li ] <-> ca [ _li + 1 ] ( DCa * _zfrat [ _li + 1 ] , DCa * _zfrat [ _li + 1 ] )*/
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM2( 22 +  _li ,22 +  _li)  += _term;
 _MATELM2( 22 +  _li + 1 ,22 +  _li)  -= _term;
 _term =  DCa * _zfrat [ _li + 1 ] ;
 _MATELM2( 22 +  _li ,22 +  _li + 1)  -= _term;
 _MATELM2( 22 +  _li + 1 ,22 +  _li + 1)  += _term;
 /*REACTION*/
  /* ~ HPCA [ _li ] <-> HPCA [ _li + 1 ] ( Dhpca * _zfrat [ _li + 1 ] , Dhpca * _zfrat [ _li + 1 ] )*/
 _term =  Dhpca * _zfrat [ _li + 1 ] ;
 _MATELM2( 18 +  _li ,18 +  _li)  += _term;
 _MATELM2( 18 +  _li + 1 ,18 +  _li)  -= _term;
 _term =  Dhpca * _zfrat [ _li + 1 ] ;
 _MATELM2( 18 +  _li ,18 +  _li + 1)  -= _term;
 _MATELM2( 18 +  _li + 1 ,18 +  _li + 1)  += _term;
 /*REACTION*/
  /* ~ CaHPCA [ _li ] <-> CaHPCA [ _li + 1 ] ( Dcahpca * _zfrat [ _li + 1 ] , Dcahpca * _zfrat [ _li + 1 ] )*/
 _term =  Dcahpca * _zfrat [ _li + 1 ] ;
 _MATELM2( 13 +  _li ,13 +  _li)  += _term;
 _MATELM2( 13 +  _li + 1 ,13 +  _li)  -= _term;
 _term =  Dcahpca * _zfrat [ _li + 1 ] ;
 _MATELM2( 13 +  _li ,13 +  _li + 1)  -= _term;
 _MATELM2( 13 +  _li + 1 ,13 +  _li + 1)  += _term;
 /*REACTION*/
  /* ~ Ca2HPCA [ _li ] <-> Ca2HPCA [ _li + 1 ] ( Dca2hpca * _zfrat [ _li + 1 ] , Dca2hpca * _zfrat [ _li + 1 ] )*/
 _term =  Dca2hpca * _zfrat [ _li + 1 ] ;
 _MATELM2( 9 +  _li ,9 +  _li)  += _term;
 _MATELM2( 9 +  _li + 1 ,9 +  _li)  -= _term;
 _term =  Dca2hpca * _zfrat [ _li + 1 ] ;
 _MATELM2( 9 +  _li ,9 +  _li + 1)  -= _term;
 _MATELM2( 9 +  _li + 1 ,9 +  _li + 1)  += _term;
 /*REACTION*/
  /* ~ Bufer [ _li ] <-> Bufer [ _li + 1 ] ( D_Bufer * _zfrat [ _li + 1 ] , D_Bufer * _zfrat [ _li + 1 ] )*/
 _term =  D_Bufer * _zfrat [ _li + 1 ] ;
 _MATELM2( 1 +  _li ,1 +  _li)  += _term;
 _MATELM2( 1 +  _li + 1 ,1 +  _li)  -= _term;
 _term =  D_Bufer * _zfrat [ _li + 1 ] ;
 _MATELM2( 1 +  _li ,1 +  _li + 1)  -= _term;
 _MATELM2( 1 +  _li + 1 ,1 +  _li + 1)  += _term;
 /*REACTION*/
  } }
 {int  _li ;for ( _li = 0 ; _li <= 4 - 1 ; _li ++ ) {
 _zdsqvol = _zdsq * Volume [ _li ] ;
 /* ~ ca [ _li ] + HPCA [ _li ] <-> CaHPCA [ _li ] ( k1HPCA * _zdsqvol , k2HPCA * _zdsqvol )*/
 _term =  k1HPCA * _zdsqvol * ca [ _li] ;
 _MATELM2( 18 +  _li ,18 +  _li)  += _term;
 _MATELM2( 22 +  _li ,18 +  _li)  += _term;
 _MATELM2( 13 +  _li ,18 +  _li)  -= _term;
 _term =  k1HPCA * _zdsqvol * HPCA [ _li] ;
 _MATELM2( 18 +  _li ,22 +  _li)  += _term;
 _MATELM2( 22 +  _li ,22 +  _li)  += _term;
 _MATELM2( 13 +  _li ,22 +  _li)  -= _term;
 _term =  k2HPCA * _zdsqvol ;
 _MATELM2( 18 +  _li ,13 +  _li)  -= _term;
 _MATELM2( 22 +  _li ,13 +  _li)  -= _term;
 _MATELM2( 13 +  _li ,13 +  _li)  += _term;
 /*REACTION*/
  /* ~ ca [ _li ] + CaHPCA [ _li ] <-> Ca2HPCA [ _li ] ( k3HPCA * _zdsqvol , k4HPCA * _zdsqvol )*/
 _term =  k3HPCA * _zdsqvol * ca [ _li] ;
 _MATELM2( 13 +  _li ,13 +  _li)  += _term;
 _MATELM2( 22 +  _li ,13 +  _li)  += _term;
 _MATELM2( 9 +  _li ,13 +  _li)  -= _term;
 _term =  k3HPCA * _zdsqvol * CaHPCA [ _li] ;
 _MATELM2( 13 +  _li ,22 +  _li)  += _term;
 _MATELM2( 22 +  _li ,22 +  _li)  += _term;
 _MATELM2( 9 +  _li ,22 +  _li)  -= _term;
 _term =  k4HPCA * _zdsqvol ;
 _MATELM2( 13 +  _li ,9 +  _li)  -= _term;
 _MATELM2( 22 +  _li ,9 +  _li)  -= _term;
 _MATELM2( 9 +  _li ,9 +  _li)  += _term;
 /*REACTION*/
  /* ~ ca [ _li ] + Bufer [ _li ] <-> CaBufer [ _li ] ( k1bufer * _zdsqvol , k2bufer * _zdsqvol )*/
 _term =  k1bufer * _zdsqvol * ca [ _li] ;
 _MATELM2( 1 +  _li ,1 +  _li)  += _term;
 _MATELM2( 22 +  _li ,1 +  _li)  += _term;
 _MATELM2( 5 +  _li ,1 +  _li)  -= _term;
 _term =  k1bufer * _zdsqvol * Bufer [ _li] ;
 _MATELM2( 1 +  _li ,22 +  _li)  += _term;
 _MATELM2( 22 +  _li ,22 +  _li)  += _term;
 _MATELM2( 5 +  _li ,22 +  _li)  -= _term;
 _term =  k2bufer * _zdsqvol ;
 _MATELM2( 1 +  _li ,5 +  _li)  -= _term;
 _MATELM2( 22 +  _li ,5 +  _li)  -= _term;
 _MATELM2( 5 +  _li ,5 +  _li)  += _term;
 /*REACTION*/
  } }
 /* ~ Ca2HPCA [ 0 ] <-> HPCA_m ( k7HPCA * _zdsq * Volume [ 0 ] , k8HPCA * parea * ( 1e10 ) )*/
 _term =  k7HPCA * _zdsq * Volume [ 0 ] ;
 _MATELM2( 9 +  0 ,9 +  0)  += _term;
 _MATELM2( 17 ,9 +  0)  -= _term;
 _term =  k8HPCA * parea * ( 1e10 ) ;
 _MATELM2( 9 +  0 ,17)  -= _term;
 _MATELM2( 17 ,17)  += _term;
 /*REACTION*/
  HPCA_z = _zdsq * ( HPCA [ 0 ] * Volume [ 0 ] + HPCA [ 1 ] * Volume [ 1 ] + HPCA [ 2 ] * Volume [ 2 ] + HPCA [ 3 ] * Volume [ 3 ] ) ;
 CaHPCA_z = _zdsq * ( CaHPCA [ 0 ] * Volume [ 0 ] + CaHPCA [ 1 ] * Volume [ 1 ] + CaHPCA [ 2 ] * Volume [ 2 ] + CaHPCA [ 3 ] * Volume [ 3 ] ) ;
 Ca2HPCA_z = _zdsq * ( Ca2HPCA [ 0 ] * Volume [ 0 ] + Ca2HPCA [ 1 ] * Volume [ 1 ] + Ca2HPCA [ 2 ] * Volume [ 2 ] + Ca2HPCA [ 3 ] * Volume [ 3 ] ) ;
 HPCA_m_z = HPCA_m * parea * ( 1e10 ) ;
 HPCA_tot_z = HPCA_z + CaHPCA_z + Ca2HPCA_z + HPCA_m_z ;
   } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(int _type){ hoc_execerror("hpca3", "cannot be used with CVODE"); return 0;}
 
static void _thread_mem_init(Datum* _thread) {
   _thread[2]._pval = (double*)ecalloc(8, sizeof(double));
  if (_thread1data_inuse) {_thread[_gth]._pval = (double*)ecalloc(5, sizeof(double));
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
 static void* _difspace1;
extern double nrn_nernst_coef();
static double _difcoef1(int _i, double* _p, Datum* _ppvar, double* _pdvol, double* _pdfcdc, Datum* _thread, _NrnThread* _nt) {
   *_pdvol =  _zdsq * Volume [ ((int) _i ) ] ;
 if (_i ==  0) {
  *_pdfcdc = nrn_nernst_coef(_type_ica)*( ( - ( _ion_dicadv  - ica_pmp_last ) * PI * diam / ( 2.0 * FARADAY ) ));
 }else{ *_pdfcdc=0.;}
   return DCa * _zdsq * Volume [ ((int) _i ) ] ;
}
 static void* _difspace2;
extern double nrn_nernst_coef();
static double _difcoef2(int _i, double* _p, Datum* _ppvar, double* _pdvol, double* _pdfcdc, Datum* _thread, _NrnThread* _nt) {
   *_pdvol =  _zdsq * Volume [ ((int) _i ) ] ; *_pdfcdc=0.;
   return Dhpca * _zdsq * Volume [ ((int) _i ) ] ;
}
 static void* _difspace3;
extern double nrn_nernst_coef();
static double _difcoef3(int _i, double* _p, Datum* _ppvar, double* _pdvol, double* _pdfcdc, Datum* _thread, _NrnThread* _nt) {
   *_pdvol =  _zdsq * Volume [ ((int) _i ) ] ; *_pdfcdc=0.;
   return Dcahpca * _zdsq * Volume [ ((int) _i ) ] ;
}
 static void* _difspace4;
extern double nrn_nernst_coef();
static double _difcoef4(int _i, double* _p, Datum* _ppvar, double* _pdvol, double* _pdfcdc, Datum* _thread, _NrnThread* _nt) {
   *_pdvol =  _zdsq * Volume [ ((int) _i ) ] ; *_pdfcdc=0.;
   return Dca2hpca * _zdsq * Volume [ ((int) _i ) ] ;
}
 static void* _difspace5;
extern double nrn_nernst_coef();
static double _difcoef5(int _i, double* _p, Datum* _ppvar, double* _pdvol, double* _pdfcdc, Datum* _thread, _NrnThread* _nt) {
   *_pdvol =  ( 1e10 ) * parea ; *_pdfcdc=0.;
   return Dhpca_m * parea * ( 1e10 ) ;
}
 static void* _difspace6;
extern double nrn_nernst_coef();
static double _difcoef6(int _i, double* _p, Datum* _ppvar, double* _pdvol, double* _pdfcdc, Datum* _thread, _NrnThread* _nt) {
   *_pdvol =  _zdsq * Volume [ ((int) _i ) ] ; *_pdfcdc=0.;
   return D_Bufer * _zdsq * Volume [ ((int) _i ) ] ;
}
 static void _difusfunc(ldifusfunc2_t _f, _NrnThread* _nt) {int _i;
  for (_i=0; _i < 4; ++_i) (*_f)(_mechtype, _difcoef1, &_difspace1, _i,  7, 53 , _nt);
  for (_i=0; _i < 4; ++_i) (*_f)(_mechtype, _difcoef2, &_difspace2, _i,  11, 57 , _nt);
  for (_i=0; _i < 4; ++_i) (*_f)(_mechtype, _difcoef3, &_difspace3, _i,  15, 61 , _nt);
  for (_i=0; _i < 4; ++_i) (*_f)(_mechtype, _difcoef4, &_difspace4, _i,  19, 65 , _nt);
  (*_f)(_mechtype, _difcoef5, &_difspace5, 0,  23, 69 , _nt);
  for (_i=0; _i < 4; ++_i) (*_f)(_mechtype, _difcoef6, &_difspace6, _i,  32, 78 , _nt);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
 for (_i=0; _i<4; _i++) Bufer[_i] = Bufer0;
 for (_i=0; _i<4; _i++) CaBufer[_i] = CaBufer0;
  Ca2HPCA_z = Ca2HPCA_z0;
  CaHPCA_z = CaHPCA_z0;
 for (_i=0; _i<4; _i++) Ca2HPCA[_i] = Ca2HPCA0;
 for (_i=0; _i<4; _i++) CaHPCA[_i] = CaHPCA0;
  HPCA_tot_z = HPCA_tot_z0;
  HPCA_z = HPCA_z0;
  HPCA_m = HPCA_m0;
 for (_i=0; _i<4; _i++) HPCA[_i] = HPCA0;
  HPCA_m_z = HPCA_m_z0;
 for (_i=0; _i<4; _i++) ca[_i] = ca0;
  n = n0;
  pumpca = pumpca0;
  pump = pump0;
 {
   _NMODLMUTEXLOCK
 if ( _zfactors_done  == 0.0 ) {
     _zfactors_done = 1.0 ;
     factors ( _threadargs_ ) ;
     }
   _NMODLMUTEXUNLOCK
 cai = cai0 ;
   B0 = Bufer0 / ( 1.0 + ( cai * k1bufer / k2bufer ) ) ;
   {int  _li ;for ( _li = 0 ; _li <= 4 - 1 ; _li ++ ) {
     ca [ _li ] = cai ;
     ca1 = cai ;
     ca2 = cai ;
     ca3 = cai ;
     HPCA [ _li ] = TotalHPCA ;
     Bufer [ _li ] = B0 ;
     CaBufer [ _li ] = Bufer0 - B0 ;
     } }
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
 {  sparse_thread(&_thread[_spth2]._pvoid, 27, _slist2, _dlist2, _p, &t, dt, scheme, _linmat2, _ppvar, _thread, _nt);
     if (secondorder) {
    int _i;
    for (_i = 0; _i < 27; ++_i) {
      _p[_slist2[_i]] += dt*_p[_dlist2[_i]];
    }}
 } {   states(_p, _ppvar, _thread, _nt);
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
 for(_i=0;_i<4;_i++){_slist2[1+_i] = (Bufer + _i) - _p;  _dlist2[1+_i] = (DBufer + _i) - _p;}
 for(_i=0;_i<4;_i++){_slist2[5+_i] = (CaBufer + _i) - _p;  _dlist2[5+_i] = (DCaBufer + _i) - _p;}
 for(_i=0;_i<4;_i++){_slist2[9+_i] = (Ca2HPCA + _i) - _p;  _dlist2[9+_i] = (DCa2HPCA + _i) - _p;}
 for(_i=0;_i<4;_i++){_slist2[13+_i] = (CaHPCA + _i) - _p;  _dlist2[13+_i] = (DCaHPCA + _i) - _p;}
 _slist2[17] = &(HPCA_m) - _p;  _dlist2[17] = &(DHPCA_m) - _p;
 for(_i=0;_i<4;_i++){_slist2[18+_i] = (HPCA + _i) - _p;  _dlist2[18+_i] = (DHPCA + _i) - _p;}
 for(_i=0;_i<4;_i++){_slist2[22+_i] = (ca + _i) - _p;  _dlist2[22+_i] = (Dca + _i) - _p;}
 _slist2[26] = &(pump) - _p;  _dlist2[26] = &(Dpump) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/arsentii/hippocalcin/HPCA-CA1/mechanism/hpca3.mod";
static const char* nmodl_file_text = 
  "NEURON {\n"
  "	SUFFIX hpca3\n"
  "	USEION ca READ cao, ica, cai  WRITE cai, ica\n"
  "	USEION k READ ek WRITE ik\n"
  "	RANGE HPCA_m_z, ca, ca1, ca2, ca3, ca_avg, ica_pmp, gbar, ik\n"
  "	GLOBAL Volume,Ra, cai0,  Rb, caix,q10, temp, tadj, vmin, vmax\n"
  "	THREADSAFE\n"
  "}\n"
  "\n"
  "DEFINE N 4 : no. of shells \n"
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
  "	DCa = 0.22 (um2/ms) Dhpca = 0.05(um2/ms)\n"
  "	Dcahpca = 0.05 (um2/ms)\n"
  "	Dca2hpca = 0.05 (um2/ms) Dhpca_m = 0.001 (um2/ms)\n"
  "	k1HPCA = 40 (/mM-ms)\n"
  "	k2HPCA = 0.01 (/ms)\n"
  "	k3HPCA = 40 (/mM-ms)\n"
  "	k4HPCA = 0.01 (/ms)\n"
  "	k7HPCA = 0.01 (/mM-ms) : insertion to the membrane\n"
  "	k8HPCA = 0.002 (/ms) : uninsertion from the membrane\n"
  "	TotalHPCA = 0.03821 (mM)\n"
  "	\n"
  "	D_Bufer = 0.05 (um2/ms)\n"
  "	Bufer0 = 20 (mM) : initial concentration of the buffer\n"
  "	k1bufer = 10 (/mM-ms)\n"
  "	k2bufer = 1 (/ms)\n"
  "	\n"
  "	k1Pump = 1 (/mM-ms)\n"
  "	k2Pump = 0.0003 (/ms)\n"
  "	TotalPump = 1e-11 (mol/cm2)\n"
  "	cai0 = 100e-6 (mM) : initial [Ca2+]_i, 110 * 10^(-6) mM = 110 nM.\n"
  "    tau_d = 200 (ms)\n"
  "	delta = 0.1 (um)\n"
  "	\n"
  "	gbar = 600   	(pS/um2) : where does this come from? = 60 mS / cm2 = 0.06 S/cm2\n"
  "	caix = 1\n"
  "	Ra   = 0.01	(/ms)\n"
  "	Rb   = 0.02	(/ms)\n"
  "	temp = 36	(degC)\n"
  "	q10  = 2.3        : temperature adjustment parameter\n"
  "	vmin = -120	(mV)\n"
  "	vmax = 100	(mV)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	diam	(um)\n"
  "	ica		(mA/cm2)\n"
  "	cai		(mM)\n"
  "    ca1 (mM)\n"
  "    ca2 (mM)\n"
  "    ca3 (mM)\n"
  "    ca_avg (mM)\n"
  "	Volume[N] (um2)\n"
  "	B0      (mM)\n"
  "	HP0   (mM)\n"
  "	cao (mM)\n"
  "	ica_pmp (mA/cm2)\n"
  "    ica_pmp_last (mA/cm2) \n"
  "	parea (um)\n"
  "	a		(/ms)\n"
  "	b		(/ms)\n"
  "	ik 		(mA/cm2)\n"
  "	gk		(pS/um2)\n"
  "	ek		(mV)\n"
  "	ninf\n"
  "	ntau 		(ms)	\n"
  "	tadj\n"
  "}\n"
  "\n"
  "CONSTANT { volo = 1e10 (um2) }\n"
  "\n"
  "STATE {\n"
  "	ca [N]			(mM)	 <1e-6>\n"
  "	HPCA [N] 		(mM)\n"
  "	CaHPCA [N] 		(mM)\n"
  "	Ca2HPCA[N] 		(mM)\n"
  "	HPCA_m         (mol/cm2)\n"
  "	\n"
  "	pump (mol/cm2)          <1e-16>\n"
  "	pumpca (mol/cm2)        <1e-16>\n"
  "	n\n"
  "	\n"
  "	HPCA_z (mM)\n"
  "	CaHPCA_z (mM)\n"
  "	Ca2HPCA_z (mM)\n"
  "	HPCA_m_z (mM)\n"
  "	HPCA_tot_z (mM)\n"
  "	\n"
  "	Bufer[N] (mM)\n"
  "	CaBufer[N] (mM)\n"
  "}\n"
  "LOCAL factors_done, nexp\n"
  "\n"
  "INITIAL {\n"
  "	MUTEXLOCK\n"
  "	if (factors_done == 0) {\n"
  "		factors_done = 1\n"
  "		factors()\n"
  "	}\n"
  "	MUTEXUNLOCK\n"
  "	cai = cai0\n"
  "	B0 =  Bufer0/(1 + (cai*k1bufer/k2bufer))\n"
  "	FROM i=0 TO N-1 {\n"
  "		ca[i] = cai\n"
  "        ca1 = cai\n"
  "        ca2 = cai\n"
  "        ca3 = cai\n"
  "		HPCA[i] = TotalHPCA\n"
  "		Bufer[i] = B0\n"
  "		CaBufer[i] = Bufer0 - B0\n"
  "	}\n"
  "	parea = PI*diam\n"
  "	pump = TotalPump/(1 + (cai*k1Pump/k2Pump))\n"
  "	pumpca = TotalPump - pump\n"
  "    ica_pmp_last = 0\n"
  "	rates()\n"
  "	n = ninf\n"
  "}\n"
  "BREAKPOINT { \n"
  "	SOLVE scheme METHOD sparse\n"
  "    ica_pmp_last = ica_pmp\n"
  "	ica = ica_pmp\n"
  "	SOLVE states METHOD cnexp\n"
  "	gk = tadj*gbar*n\n"
  "	ik = (1e-4) * gk * (v - ek) : (1e-4) converts pS/um2 to S/cm2\n"
  "}\n"
  "\n"
  "\n"
  "DERIVATIVE states {\n"
  "	cai = ca[0]\n"
  "    ca1 = ca[1]\n"
  "    ca2 = ca[2]\n"
  "    ca3 = ca[3]\n"
  "\n"
  "	rates()\n"
  "	n' =  (ninf-n)/ntau\n"
  "}\n"
  "\n"
  "LOCAL dsq, dsqvol\n"
  "LOCAL frat[N] : scales the rate constants for model geometry\n"
  "\n"
  "KINETIC scheme {\n"
  "	dsq = diam*diam\n"
  "    : multiplies right hand-sides of diff. equations by the volume\n"
  "	COMPARTMENT (1e10)*parea {pump pumpca HPCA_m}\n"
  "	COMPARTMENT volo {cao}\n"
  "	COMPARTMENT i, dsq*Volume[i] {ca HPCA CaHPCA Ca2HPCA Bufer CaBufer}\n"
  "    \n"
  "    : diffusion between segments\n"
  "	LONGITUDINAL_DIFFUSION i, DCa*dsq*Volume[i] {ca}\n"
  "	LONGITUDINAL_DIFFUSION i, Dhpca*dsq*Volume[i] {HPCA}\n"
  "	LONGITUDINAL_DIFFUSION i, Dcahpca*dsq*Volume[i] {CaHPCA}\n"
  "	LONGITUDINAL_DIFFUSION i, Dca2hpca*dsq*Volume[i] {Ca2HPCA}\n"
  "	LONGITUDINAL_DIFFUSION  Dhpca_m*parea*(1e10) {HPCA_m}\n"
  "	LONGITUDINAL_DIFFUSION i, D_Bufer*dsq*Volume[i] {Bufer}\n"
  "	\n"
  "	: kinetic equations for the Ca2+-ATPase\n"
  "	~ ca[0] + pump <-> pumpca (k1Pump*parea*(1e10), k2Pump*parea*(1e10))\n"
  "	~ pumpca <-> pump + cao (k1Pump*parea*(1e10), k2Pump*parea*(1e10))\n"
  "	CONSERVE pump + pumpca = TotalPump * parea * (1e10)\n"
  "	ica_pmp = 2*FARADAY*(f_flux - b_flux)/parea\n"
  "    : ica_pmp is the \"new\" value, but cashell must be \n"
  "    : computed using the \"old\" value, i.e. ica_pmp_last\n"
  "	: all currents except pump\n"
  "	~ ca[0] << (-(ica - ica_pmp_last)*PI*diam/(2*FARADAY))\n"
  "	\n"
  "	FROM i=0 TO N-2 {\n"
  "		~ ca[i] <-> ca[i+1] (DCa*frat[i+1], DCa*frat[i+1])\n"
  "		~ HPCA[i] <-> HPCA[i+1] (Dhpca*frat[i+1], Dhpca*frat[i+1])\n"
  "		~ CaHPCA[i] <-> CaHPCA[i+1] (Dcahpca*frat[i+1], Dcahpca*frat[i+1])\n"
  "		~ Ca2HPCA[i] <-> Ca2HPCA[i+1] (Dca2hpca*frat[i+1], Dca2hpca*frat[i+1])\n"
  "		~ Bufer[i] <-> Bufer[i+1] (D_Bufer*frat[i+1], D_Bufer*frat[i+1])\n"
  "	}\n"
  "	FROM i=0 TO N-1 {\n"
  "		dsqvol = dsq*Volume[i]\n"
  "		~ ca[i] + HPCA[i] <-> CaHPCA[i] (k1HPCA*dsqvol, k2HPCA*dsqvol)\n"
  "		~ ca[i] + CaHPCA[i] <-> Ca2HPCA[i] (k3HPCA*dsqvol, k4HPCA*dsqvol)\n"
  "		~ ca[i] + Bufer[i] <-> CaBufer[i] (k1bufer*dsqvol, k2bufer*dsqvol)\n"
  "	}\n"
  "	~ Ca2HPCA[0] <-> HPCA_m (k7HPCA*dsq*Volume[0], k8HPCA*parea*(1e10)) \n"
  "    : Absolute amounts of substances (moles)	\n"
  "\n"
  "	HPCA_z = dsq*(HPCA[0]*Volume[0]+HPCA[1]*Volume[1] + HPCA[2]*Volume[2] + HPCA[3]*Volume[3])\n"
  "	\n"
  "	CaHPCA_z = dsq*(CaHPCA[0]*Volume[0] + CaHPCA[1]*Volume[1] + CaHPCA[2]*Volume[2] + CaHPCA[3]*Volume[3])\n"
  "	\n"
  "	Ca2HPCA_z = dsq*(Ca2HPCA[0]*Volume[0] + Ca2HPCA[1]*Volume[1] + Ca2HPCA[2]*Volume[2] + Ca2HPCA[3]*Volume[3])\n"
  "	HPCA_m_z = HPCA_m*parea*(1e10)\n"
  "	HPCA_tot_z = HPCA_z + CaHPCA_z + Ca2HPCA_z + HPCA_m_z\n"
  "}\n"
  "\n"
  "PROCEDURE rates() {  \n"
  "	a = Ra * HPCA_m\n"
  "	b = Rb\n"
  "	tadj = q10^((celsius - temp)/10)\n"
  "	ntau = 1/tadj/(a+b)\n"
  "	ninf = a/(a+b)\n"
  "}\n"
  "\n"
  "\n"
  "PROCEDURE factors() {\n"
  "	LOCAL r, dr2\n"
  "	r = 1/2\n"
  "	dr2 = r/(N-1)/2\n"
  "	Volume[0] = 0 frat[0] = 2*r FROM i=0 TO N-2 {\n"
  "		Volume[i] = Volume[i] + PI*(r-dr2/2)*2*dr2\n"
  "		r = r - dr2\n"
  "		frat[i+1] = 2*PI*r/(2*dr2)\n"
  "		r = r - dr2\n"
  "		Volume[i+1] = PI*(r+dr2/2)*2*dr2\n"
  "	}\n"
  "}\n"
  ;
#endif

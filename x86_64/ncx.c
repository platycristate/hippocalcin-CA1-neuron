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
 
#define nrn_init _nrn_init__ncx
#define _nrn_initial _nrn_initial__ncx
#define nrn_cur _nrn_cur__ncx
#define _nrn_current _nrn_current__ncx
#define nrn_jacob _nrn_jacob__ncx
#define nrn_state _nrn_state__ncx
#define _net_receive _net_receive__ncx 
 
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
#define imax _p[0]
#define ica _p[1]
#define ina _p[2]
#define itot _p[3]
#define icont _p[4]
#define rate _p[5]
#define cao _p[6]
#define cai _p[7]
#define nao _p[8]
#define nai _p[9]
#define v _p[10]
#define _g _p[11]
#define _ion_cao	*_ppvar[0]._pval
#define _ion_cai	*_ppvar[1]._pval
#define _ion_ica	*_ppvar[2]._pval
#define _ion_dicadv	*_ppvar[3]._pval
#define _ion_nao	*_ppvar[4]._pval
#define _ion_nai	*_ppvar[5]._pval
#define _ion_ina	*_ppvar[6]._pval
#define _ion_dinadv	*_ppvar[7]._pval
 
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
 static void _hoc_pumprate(void);
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
 "setdata_ncx", _hoc_setdata,
 "pumprate_ncx", _hoc_pumprate,
 0, 0
};
#define pumprate pumprate_ncx
 extern double pumprate( _threadargsprotocomma_ double , double , double , double , double );
 /* declare global and static user variables */
#define cont_factor cont_factor_ncx
 double cont_factor = -1;
#define gamma gamma_ncx
 double gamma = 0.35;
#define is_fixed is_fixed_ncx
 double is_fixed = 0;
#define ksat ksat_ncx
 double ksat = 0.1;
#define kca kca_ncx
 double kca = 1.38;
#define kna kna_ncx
 double kna = 87.5;
#define naf naf_ncx
 double naf = 15;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "kna_ncx", "mM",
 "kca_ncx", "mM",
 "cont_factor_ncx", "1",
 "ksat_ncx", "1",
 "naf_ncx", "mM",
 "is_fixed_ncx", "1",
 "imax_ncx", "mA/cm2",
 "ica_ncx", "mA/cm2",
 "ina_ncx", "mA/cm2",
 "itot_ncx", "mA/cm2",
 "icont_ncx", "mA/cm2",
 "rate_ncx", "mA/cm2",
 0,0
};
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "kna_ncx", &kna_ncx,
 "kca_ncx", &kca_ncx,
 "gamma_ncx", &gamma_ncx,
 "cont_factor_ncx", &cont_factor_ncx,
 "ksat_ncx", &ksat_ncx,
 "naf_ncx", &naf_ncx,
 "is_fixed_ncx", &is_fixed_ncx,
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
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"ncx",
 "imax_ncx",
 0,
 "ica_ncx",
 "ina_ncx",
 "itot_ncx",
 "icont_ncx",
 "rate_ncx",
 0,
 0,
 0};
 static Symbol* _ca_sym;
 static Symbol* _na_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 12, _prop);
 	/*initialize range parameters*/
 	imax = 1.2;
 	_prop->param = _p;
 	_prop->param_size = 12;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 8, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0]._pval = &prop_ion->param[2]; /* cao */
 	_ppvar[1]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[4]._pval = &prop_ion->param[2]; /* nao */
 	_ppvar[5]._pval = &prop_ion->param[1]; /* nai */
 	_ppvar[6]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[7]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 
}
 static void _initlists();
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _ncx_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	ion_reg("na", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	_na_sym = hoc_lookup("na_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 12, 8);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 5, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 6, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 7, "na_ion");
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 ncx /home/arsentii/hippocalcin/HPCA-CA1/mechanism/ncx.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double F = 96485.3;
 static double R = 8.3145;
static int _reset;
static char *modelname = "sodium calcium exchange";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
double pumprate ( _threadargsprotocomma_ double _lv , double _lnai , double _lnao , double _lcai , double _lcao ) {
   double _lpumprate;
 double _lq10 , _lKqa , _lKB , _lk ;
 _lk = R * ( celsius + 273.14 ) / ( F * 1e-3 ) ;
   _lq10 = pow( 3.0 , ( ( celsius - 37.0 ) / 10.0 ) ) ;
   _lKqa = exp ( gamma * _lv / _lk ) ;
   _lKB = exp ( ( gamma - 1.0 ) * _lv / _lk ) ;
   _lpumprate = _lq10 * imax * ( _lKqa * _lnai * _lnai * _lnai * _lcao - _lKB * _lnao * _lnao * _lnao * _lcai ) / ( ( kna * kna * kna + _lnao * _lnao * _lnao ) * ( kca + _lcao ) * ( 1.0 + ksat * _lKB ) ) ;
   
return _lpumprate;
 }
 
static void _hoc_pumprate(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  pumprate ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) , *getarg(5) );
 hoc_retpushx(_r);
}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 2);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 3, 4);
   nrn_update_ion_pointer(_na_sym, _ppvar, 4, 2);
   nrn_update_ion_pointer(_na_sym, _ppvar, 5, 1);
   nrn_update_ion_pointer(_na_sym, _ppvar, 6, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 7, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{

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
  cai = _ion_cai;
  nao = _ion_nao;
  nai = _ion_nai;
 initmodel(_p, _ppvar, _thread, _nt);
  }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   if ( is_fixed  == 0.0 ) {
     rate = pumprate ( _threadargscomma_ v , nai , nao , cai , cao ) ;
     }
   if ( is_fixed  == 1.0 ) {
     rate = pumprate ( _threadargscomma_ v , naf , nao , cai , cao ) ;
     }
   ina = 3.0 * rate ;
   ica = - 2.0 * rate ;
   itot = ina + ica ;
   icont = itot * cont_factor ;
   }
 _current += ica;
 _current += ina;
 _current += icont;

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
  cai = _ion_cai;
  nao = _ion_nao;
  nai = _ion_nai;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dina;
 double _dica;
  _dica = ica;
  _dina = ina;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dicadv += (_dica - ica)/.001 ;
  _ion_dinadv += (_dina - ina)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ica += ica ;
  _ion_ina += ina ;
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

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/arsentii/hippocalcin/HPCA-CA1/mechanism/ncx.mod";
static const char* nmodl_file_text = 
  "TITLE sodium calcium exchange\n"
  ": taken from Courtemanche et al Am J Physiol 1998 275:H301\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX ncx\n"
  "	THREADSAFE\n"
  "	USEION ca READ cao, cai WRITE ica\n"
  "	USEION na READ nao, nai WRITE ina\n"
  "	RANGE ica, ina , itot, imax, rate\n"
  "	GLOBAL kna, kca, gamma, cont_factor, ksat, naf, is_fixed\n"
  "    NONSPECIFIC_CURRENT icont\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "	F = (faraday) (coulombs)\n"
  "	R 	= (k-mole)	(joule/degC)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	imax	= 1.2       (mA/cm2) \n"
  "	kna	=  87.5     (mM)\n"
  "	kca	=  1.38     (mM)\n"
  "	gamma	= .35		: voltage dependence factor\n"
  "    cont_factor = -1    (1)\n"
  "    ksat = 0.1          (1)\n"
  "    naf = 15.0      (mM)\n"
  "    is_fixed = 0        (1)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	celsius	(degC)\n"
  "	v	(mV)\n"
  "	ica	(mA/cm2)\n"
  "	ina	(mA/cm2)\n"
  "	itot	(mA/cm2)\n"
  "    icont   (mA/cm2)\n"
  "    rate    (mA/cm2)\n"
  "	cao	(mM)\n"
  "    cai	(mM)\n"
  "	nao	(mM)\n"
  "	nai	(mM)\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	:LOCAL rate\n"
  "    if (is_fixed==0) {\n"
  "        rate = pumprate(v,nai,nao,cai,cao)\n"
  "    }\n"
  "    if (is_fixed==1) {\n"
  "        rate = pumprate(v,naf,nao,cai,cao)\n"
  "    }\n"
  "	ina =  3*rate\n"
  "	ica = -2*rate\n"
  "	itot=ina+ica\n"
  "    icont=itot*cont_factor\n"
  "}\n"
  "\n"
  "FUNCTION pumprate(v,nai,nao,cai,cao) {\n"
  "	LOCAL q10, Kqa, KB, k\n"
  "	k = R*(celsius + 273.14)/(F*1e-3)\n"
  "	q10 = 3^((celsius - 37)/10 (degC))\n"
  "	Kqa = exp(gamma*v/k)\n"
  "	KB = exp( (gamma - 1)*v/k)\n"
  "	pumprate = q10*imax*(Kqa*nai*nai*nai*cao-KB*nao*nao*nao*cai)/((kna*kna*kna + nao*nao*nao)*(kca + cao)*(1 + ksat*KB))\n"
  "}\n"
  ;
#endif

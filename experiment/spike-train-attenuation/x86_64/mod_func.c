#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern void _cad_reg(void);
extern void _cagk_reg(void);
extern void _calH_reg(void);
extern void _cal_reg(void);
extern void _car_reg(void);
extern void _cat_reg(void);
extern void _d3_reg(void);
extern void _gabaa_reg(void);
extern void _gabab_reg(void);
extern void _glutamate_reg(void);
extern void _hha2_reg(void);
extern void _hha_old_reg(void);
extern void _h_reg(void);
extern void _hpca2_reg(void);
extern void _hpca3_reg(void);
extern void _ipulse2_reg(void);
extern void _kadist_reg(void);
extern void _kaprox_reg(void);
extern void _kca_reg(void);
extern void _km_reg(void);
extern void _nap_reg(void);
extern void _ncx_reg(void);
extern void _nmda_reg(void);
extern void _SimpleAMPA_NMDA_reg(void);
extern void _somacar_reg(void);
extern void _vecevent_reg(void);

void modl_reg(){
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");

    fprintf(stderr," \"mechanism//cad.mod\"");
    fprintf(stderr," \"mechanism//cagk.mod\"");
    fprintf(stderr," \"mechanism//calH.mod\"");
    fprintf(stderr," \"mechanism//cal.mod\"");
    fprintf(stderr," \"mechanism//car.mod\"");
    fprintf(stderr," \"mechanism//cat.mod\"");
    fprintf(stderr," \"mechanism//d3.mod\"");
    fprintf(stderr," \"mechanism//gabaa.mod\"");
    fprintf(stderr," \"mechanism//gabab.mod\"");
    fprintf(stderr," \"mechanism//glutamate.mod\"");
    fprintf(stderr," \"mechanism//hha2.mod\"");
    fprintf(stderr," \"mechanism//hha_old.mod\"");
    fprintf(stderr," \"mechanism//h.mod\"");
    fprintf(stderr," \"mechanism//hpca2.mod\"");
    fprintf(stderr," \"mechanism//hpca3.mod\"");
    fprintf(stderr," \"mechanism//ipulse2.mod\"");
    fprintf(stderr," \"mechanism//kadist.mod\"");
    fprintf(stderr," \"mechanism//kaprox.mod\"");
    fprintf(stderr," \"mechanism//kca.mod\"");
    fprintf(stderr," \"mechanism//km.mod\"");
    fprintf(stderr," \"mechanism//nap.mod\"");
    fprintf(stderr," \"mechanism//ncx.mod\"");
    fprintf(stderr," \"mechanism//nmda.mod\"");
    fprintf(stderr," \"mechanism//SimpleAMPA_NMDA.mod\"");
    fprintf(stderr," \"mechanism//somacar.mod\"");
    fprintf(stderr," \"mechanism//vecevent.mod\"");
    fprintf(stderr, "\n");
  }
  _cad_reg();
  _cagk_reg();
  _calH_reg();
  _cal_reg();
  _car_reg();
  _cat_reg();
  _d3_reg();
  _gabaa_reg();
  _gabab_reg();
  _glutamate_reg();
  _hha2_reg();
  _hha_old_reg();
  _h_reg();
  _hpca2_reg();
  _hpca3_reg();
  _ipulse2_reg();
  _kadist_reg();
  _kaprox_reg();
  _kca_reg();
  _km_reg();
  _nap_reg();
  _ncx_reg();
  _nmda_reg();
  _SimpleAMPA_NMDA_reg();
  _somacar_reg();
  _vecevent_reg();
}

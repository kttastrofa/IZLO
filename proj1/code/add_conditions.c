#include <stddef.h>
#include "cnf.h"

//
// LOGIN: xmeciak00
//

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 1)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
// Pole streets ma velikost num_of_streets a obsahuje vsechny existujuci ulice
//    - pro 0 <= i < num_of_streets predstavuje streets[i] jednu existujici
//      ulici od krizovatky streets[i].crossroad_from ke krizovatce streets[i].crossroad_to
void at_least_one_valid_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets, const Street* streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    assert(streets != NULL);

    // pre kazdy krok i
    for (unsigned i=0; i<num_of_streets; ++i) {

        Clause *cl = create_new_clause(formula);
        //kazdej ulice j
        for (unsigned j=0; j<num_of_streets; ++j) { //streets??

            // existuje nejaka ulica so zaciatkom 'z' a koncom 'k'

            add_literal_to_clause(cl, true, i, streets[j].crossroad_from, streets[j].crossroad_to);
        }
    }
}



// Tato funkce by mela do formule pridat klauzule predstavujici podminku 2)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void at_most_one_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    // pre kazdy krok
    for (unsigned i=0; i<num_of_streets; ++i) {

        //kazdeho zaciatku
        for (unsigned z1 = 0; z1 < num_of_crossroads; ++z1) {
            for (unsigned z2 = 0; z2 < num_of_crossroads; ++z2) {

                //a kazdeho konca
                    for (unsigned k1=0; k1<num_of_crossroads; ++k1) {
                        for (unsigned k2 = 0; k2 < num_of_crossroads; ++k2) {

                            //existuje najviac 1 ulica na 1 krok, veduca do inej krizovatky a zaroven ina od inej ulice
                            if ((z1!=z2 || k1!=k2) && (z1!=k1 || z2!=k2)) {
                                Clause *cl = create_new_clause(formula);
                                add_literal_to_clause(cl, false, i, z1, k1);
                                add_literal_to_clause(cl, false, i, z2, k2);

                            }
                        }
                    }
                }
            }
        }
    }




// Tato funkce by mela do formule pridat klauzule predstavujici podminku 3)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_connected(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    // pre kazdy krok
    for (unsigned i=0; i<num_of_streets-1; ++i) {
        //kazdeho zaciatku
        for (unsigned k1=0; k1<num_of_crossroads; ++k1) {
        for (unsigned z1 = 0; z1 < num_of_crossroads; ++z1) {
            Clause *cl = create_new_clause(formula);
            add_literal_to_clause(cl, false, i, z1, k1);
                //kazdeho konca
                //for (unsigned z2 = 0; z2 < num_of_crossroads; ++z2) {
                    for (unsigned k2 = 0; k2 < num_of_crossroads; ++k2) {
                        //exituje konexia konca s nejakym zaciatkom inej ulice
                        //if (k1!=z2) {
                            add_literal_to_clause(cl, true, i+1, k1, k2);

                        }
                    }
                }
            }
        }
    //}
//}


// Tato funkce by mela do formule pridat klauzule predstavujici podminku 4)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_do_not_repeat(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    for (unsigned i = 0; i < num_of_streets; ++i) {
        // pro kazdy krok i
        for (unsigned j = 0; j < num_of_streets; ++j) {
            if (i != j) {
                // pro kazdy jiny krok j
                for (unsigned z = 0; z < num_of_crossroads; ++z) {
                    for (unsigned k = 0; k < num_of_crossroads; ++k) {
                        // pro kazdu dvojici krizovatek (z, k)
                        Clause* cl = create_new_clause(formula);
                        add_literal_to_clause(cl, false, i, z, k);
                        add_literal_to_clause(cl, false, j, z, k);
                    }
                }
            }
        }
    }
}

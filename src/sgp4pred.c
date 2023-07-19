/*
This file contains miscellaneous functions required for predicting satellite overpasses and the main class for easy acces to all the functions.
Most functions are based on the columns written by Dr. T.S. Kelso on the celestrak website (https://celestrak.com/columns/)

Written by Hopperpop
*/

#include <stdint.h>

#include <sgp4/sgp4ext.h>
#include <sgp4/sgp4unit.h>
#include <sgp4/sgp4io.h>
#include <sgp4/sgp4coord.h>
#include <sgp4/brent.h>
#include <sgp4/sgp4pred.h>
#include <sgp4/visible.h>

#define MAX_itter   30
#define tol         0.000005    /* tol = +-0,432 sec */

/* Init functions */
bool sgp4_init(sgp4_t *conf, const char naam[24], char longstr1[130], char longstr2[130])
{
    conf->opsmode    = 'i';                  /* Improved mode */
    conf->whichconst = wgs84;                /* Newest constants */
    conf->sunoffset  = -0.10471975511966;    /* Sun aboven -6o => not dark enough */
    conf->offset     = 0.0;

    if (strcmp(longstr1, line1) == 0)
    {
        return false;
    }

    strlcpy(satName, naam, sizeof(satName));
    strlcpy(line1, longstr1, sizeof(line1));
    strlcpy(line2, longstr2, sizeof(line2));

    twoline2rv(longstr1, longstr2, opsmode, whichconst, satrec );

    revpday = 1440.0 / (2.0 * pi) * satrec.no;

    return true;
}

/* Set site coordinates */
void sgp4_site(sgp4_t *conf, double lat, double lon, double alt)
{
    conf->siteLat = lat;
    conf->siteLon = lon;
    conf->siteAlt = alt / 1000;  /* meters to kilometers */
    conf->siteLatRad = siteLat * pi / 180.0;
    conf->siteLonRad = siteLon * pi / 180.0;
}

/* Set sunoffset */
void sgp4_setsunrise(sgp4_t *conf, double degrees)
{
    conf->sunoffset = degrees * pi / 180.0;
}

/* Location functions */
void sgp4_findsat(sgp4_t *conf, double jdI)
{
    double latlongh[3];
    double recef[3];
    double vecef[3];
    double razelrates[3];

    conf->jdC = jdI;

    double tsince = (jdC - satrec.jdsatepoch) * 24.0 * 60.0;
    sgp4(whichconst, satrec, tsince, ro, vo);
    rv2azel(ro, siteLatRad, siteLonRad, siteAlt, jdC, razel);
    teme2ecef(ro, jdC, recef);
    ijk2ll(recef, latlongh);

    conf->satLat    = latlongh[0] * 180 / pi;                       /* Latidude sattelite (degrees) */
    conf->satLon    = latlongh[1] * 180 / pi;                       /* longitude sattelite (degrees) */
    conf->satAlt    = latlongh[2];                                  /* Altitude sattelite (degrees) */
    conf->satAz     = floatmod(razel[1] * 180 / pi + 360.0, 360.0); /* Azemith sattelite (degrees) */
    conf->satEl     = razel[2] * 180 / pi;                          /* elevation sattelite (degrees) */
    conf->satDist   = razel[0];                                     /* Distance to sattelite (km) */
    conf->satJd     = jdI;                                          /* time (julian day) */

    satVis = visible();
    if (satEl < 0.0)
    {
        satVis = -2;    /* under horizon */
    }
}

void sgp4_findsat(sgp4_t *conf, unsigned long unix)
{
    findsat(getJulianFromUnix(unix));
}

//////Predict functions/////////

/* Returns the elevation for a given julian date */
double sgp4_sgp4wrap(sgp4_t *conf, double jdCe)
{
    double tsince = (jdCe - satrec.jdsatepoch) * 24.0 * 60.0;

    sgp4(whichconst, satrec, tsince, ro, vo);
    rv2azel(ro, siteLatRad, siteLonRad, siteAlt, jdCe, razel);

    return -razel[2]+offset;
}


/* Returns next overpass maximum, starting from a maximum called startpoint */
bool sgp4_nextpass(sgp4_t *conf, passinfo *passdata, int itterations)
{
    return (Sgp4::nextpass(passdata, itterations, false, 0.0));
}

/* Returns next overpass. Set direc to false for forward search, true for backwards search */
bool sgp4_nextpass(sgp4_t *conf, passinfo *passdata, int itterations, bool direc)
{
    return (Sgp4::nextpass( passdata, itterations, direc, 0.0));
}

// returns next overpass maximum, starting from a maximum called startpoint
// direc = false for forward search, true for backwards search
// minimumElevation is the minimum elevation above the horizon in degrees. Passes which are lower than this are rejected
// returns false if all itterations are below the minimumElevation
bool sgp4_nextpass(sgp4_t *conf, passinfo *passdata, int itterations, bool direc, double minimumElevation)
{
    double range,jump;
    int i;
    double max_elevation = -1.0;
    int16_t vissum,vis;
    bool isdaylight;
    double startphi, stopphi, phi;

    range = 0.25 / revpday;

    if (direc)  /* set search direction */
    {
        jump = -1.0 / revpday;
    }
    else
    {
        jump = 1.0 / revpday;
    }

    for(i = 0; i < itterations && max_elevation <= (minimumElevation * pi / 180); i++)  /* Search for elevation above minimumElevation */
    {
       jdCp+= jump;
       max_elevation = - brentmin(jdCp - range , jdCp, jdCp + range, &Sgp4::sgp4wrap , tol, &jdCp, this);
		#ifdef ESP8266
			yield();
		#endif
    }
    jdC = jdCp;
    if (i >= itterations)
    {
        return 0;
    }

	/* Max elevation */

    (*passdata).maxelevation = (max_elevation+offset)*180/pi;
    (*passdata).jdmax = jdC;
	  (*passdata).azmax = floatmod(razel[1] * 180 / pi + 360.0, 360.0);
    vis = visible(isdaylight,phi);

    if (isdaylight)
    {
        (*passdata).vismax = daylight;
    }
    else if (vis < 1000)
    {
        (*passdata).vismax = eclipsed;
    }
    else
    {
        (*passdata).vismax = lighted;
    }

    /* Start point */

    range = 0.5 / revpday;
    jdC = zbrent(&Sgp4::sgp4wrap, jdCp, jdCp - range, tol, this);
    if (jdC < 0.0)
    {
        return 0;
    }
    (*passdata).jdstart = jdC;
    (*passdata).azstart = floatmod(razel[1] * 180 / pi + 360.0, 360.0);
    vis = visible(isdaylight, startphi);

    if (isdaylight)
    {
        (*passdata).visstart = daylight;
    }
    else if (vis < 1000)
    {
        (*passdata).visstart = eclipsed;
    }
    else
    {
        (*passdata).visstart = lighted;
    }
    vissum = vis;

    /* Stop point */

    jdC = zbrent(&Sgp4::sgp4wrap, jdCp, jdCp + range, tol, this);
    if (jdC < 0.0)
    {
        return 0;
    }
    (*passdata).jdstop = jdC;
    (*passdata).azstop = floatmod(razel[1] * 180 / pi + 360.0, 360.0);
    vis = visible(isdaylight,stopphi);

    if (isdaylight)
    {
        (*passdata).visstop = daylight;
    }
    else if (vis < 1000)
    {
        (*passdata).visstop = eclipsed;
    }
    else
    {
        (*passdata).visstop = lighted;
    }
    vissum += vis;

    /* Global visibility */

    if ((*passdata).visstop == daylight && (*passdata).visstart == daylight)
    {
        (*passdata).sight = daylight;
    }
    else if (vissum < 1000)
    {
        (*passdata).sight = eclipsed;
    }
    else
    {
        (*passdata).sight = lighted;
    }

	/* Transit */

    if (sgn(startphi) == sgn(stopphi))
    {
        (*passdata).transit = none;
        (*passdata).jdtransit = NAN;
        (*passdata).aztransit = NAN;
        (*passdata).transitelevation = NAN;
        (*passdata).vistransit = daylight;
    }
    else
    {
        if (sgn(startphi)>sgn(stopphi))
        {
            (*passdata).transit = enter;
        }
        else
        {
            (*passdata).transit = leave;
        }

        jdC = zbrent(&Sgp4::visiblewrap, (*passdata).jdstart, (*passdata).jdstop, tol, this);
        if (jdC < 0.0)
        {
            return 0;
        }
        (*passdata).jdtransit = jdC;
        (*passdata).aztransit = floatmod(razel[1] * 180 / pi + 360.0, 360.0);
        (*passdata).transitelevation = razel[2] * 180 / pi;
        vis = visible(isdaylight,phi);

        if (isdaylight)
        {
            (*passdata).vistransit = daylight;
        }
        else
        {
            (*passdata).vistransit = eclipsed;
        }
        //else {(*passdata).visstop = lighted;}
	}

    (*passdata).minelevation = offset * 180 / pi;

    return 1;
}

/* Finds a startpoint for the prediction algorithm */
bool sgp4_initpredpoint(sgp4_t *conf, double startpoint, double startelevation)
{
    double a, b, c;
    double fa, fb, fc;
    double jdI;
    int i;

    offset = startelevation * pi /180.0;

    c = startpoint;
    fc = sgp4wrap(c);
    b = startpoint - 0.166 / revpday;
    fb = sgp4wrap(b);
    a = startpoint - 0.322 / revpday;
    fa = sgp4wrap(a);

    for(i = 0; i < MAX_itter && (fb > fa || fb > fc); i++)
    {
        fc = fb;
        fb = fa;
        c = b;
        b = a;
        a = startpoint - 0.166 * (i + 3) / revpday;
        fa = sgp4wrap(a);
    }
    if (i >= MAX_itter - 1)
    {
        return 0;
    }

    brentmin(a , b, c, &Sgp4::sgp4wrap , tol, &jdI, this);
    jdCp = jdI;

    return 1;
}

bool sgp4_initpredpoint(sgp4_t *conf, unsigned long unix, double startelevation)
{
    return initpredpoint(getJulianFromUnix(unix), startelevation);
}

double sgp4_getpredpoint(sgp4_t *conf)
{
    return conf->jdCp;
}

void sgp4_setpredpoint(sgp4_t *conf, double bob)
{
    conf->jdCp = bob;
}

/** \} End of sgp4pred group */

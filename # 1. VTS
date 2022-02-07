// Test Function: VTS
ETS_PRGFLOW_FUNC VTS( int DSIndex, LPCTSTR TestLabel )
{

    RESULTS_STR vtsu[NUM_SITES],ntc[NUM_SITES], vtsu25[NUM_SITES];

	LPCTSTR STA;
	STA=GetTestMainVariable( STATION_ID );

    //////////////////////////////////////
    // Update test numbering information
    SetTestNumber( TestNmbr[DSIndex] );
    SetSubTestNumber( SubTestNmbr[DSIndex] );
     
// VTSU

	cbitclose( KS_GP, K5A_S14, K6A_S14, K5C_S14, KTSU_S14 );
	lwait( 1000 );

	sp100set( VCC_SPU100_GP, SP_FV, 15, SP_30V, SP_1A );
	lwait(10000);

	apuset( VTS_APU_GP, APU_FI, 0, APU_10V, APU_1MA, PIN_TO_VI ); //Shoud be fixed
	lwait(10000);

    apumv( VTS_APU_GP, 10, 13 );
	groupgetresults( vtsu, NUM_SITES );

	if (strncmp(STA,"LE07",4)==0) {
	vtsu[0].value=vtsu[0].value+0.04;
	vtsu[1].value=vtsu[1].value+0.04;
	vtsu[2].value=vtsu[2].value+0.04;
	vtsu[3].value=vtsu[3].value+0.04;
	}

	if (strncmp(STA,"LE10",4)==0) {
	vtsu[0].value=vtsu[0].value+0.025;
	vtsu[1].value=vtsu[1].value+0.035;
	vtsu[2].value=vtsu[2].value+0.035;
	vtsu[3].value=vtsu[3].value+0.035;
	}

	if (strncmp(STA,"LE12",4)==0) {
	vtsu[0].value=vtsu[0].value+0.04;
	vtsu[1].value=vtsu[1].value+0.04;
	vtsu[2].value=vtsu[2].value+0.04;
	vtsu[3].value=vtsu[3].value+0.04;
	}

	msLogResultAll( DSIndex++, vtsu, NUM_SITES );


    // Clean Up Code
	cbitopen( KS_GP, K8D_S14, K8C_S14, K5A_S14, K6A_S14, K5C_S14, KTSU_S14 );
	lwait( 1000 );

	sp100set( VCC_SPU100_GP, SP_FV, 0, SP_30V, SP_1MA );
	sp100set( VB_SPU100_GP, SP_FV, 0, SP_30V, SP_1MA );
	sp100set( VCC_SPU100_GP, SP_OFF, 0, SP_30V, SP_1MA );
	sp100set( VB_SPU100_GP, SP_OFF, 0, SP_30V, SP_1MA );
	apuset( VTS_APU_GP, APU_VIOFF, 0, APU_10V, APU_100UA, PIN_TO_VI );

// NTC

	cbitclose( KS_GP, KNTC_S14); // only 1 need
	lwait( 1000 );

	apuset( VTS_APU_GP, APU_FV, 5.0, APU_10V, APU_1MA, PIN_TO_VI ); 
	lwait( 10000 );
    apumi( VTS_APU_GP, 10, 13 );

	groupgetresults( ntc, NUM_SITES );

	FOR_EACH_SITE( site, NUM_SITES )
	{
		ntc[site].value = (5 / ntc[site].value)*1000;
		msLogResult(site, DSIndex, ntc[site].value);
	}
	DSIndex=DSIndex+1; IF_FAIL_RETURN;

/*
	ntc[0].value=(5/ntc[0].value)*1000;
	ntc[1].value=ntc[0].value;
	ntc[2].value=ntc[0].value;
	ntc[3].value=ntc[0].value;

	FOR_EACH_SITE( site, NUM_SITES )
		msLogResult( site, DSIndex, ntc[site].value );
	DSIndex++;  IF_FAIL_RETURN;
*/

    // Clean Up Code
   	cbitopen( KS_GP, KNTC_S14);
	lwait( 1000 ); 
	apuset( VTS_APU_GP, APU_VIOFF, 0, APU_10V, APU_100UA, PIN_TO_VI );

//VTSU25

	FOR_EACH_SITE(site,NUM_SITES) {

		if(ntc[site].value>72418.9 && ntc[site].value<73470)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.19;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);
		} 

		if(ntc[site].value>70104.2 && ntc[site].value<72418.9)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.18;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);
		} 

		if(ntc[site].value>69022.4 && ntc[site].value<70104.2)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.17;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		} 

		if(ntc[site].value>66911.2 && ntc[site].value<69022.4)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.16;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>65803.9 && ntc[site].value<66911.2)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.15;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>63881.2 && ntc[site].value<65803.9)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.14;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>62753 && ntc[site].value<63881.2)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.13;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>61005 && ntc[site].value<62753)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.12;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>59860.1 && ntc[site].value<61005)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.11;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>58273.9 && ntc[site].value<59860.1)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.1;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>57116 && ntc[site].value<58273.9)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.09;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>55679.8 && ntc[site].value<57116)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.08;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>54512.7 && ntc[site].value<55679.8)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.07;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>53215.2 && ntc[site].value<54512.7)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.06;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>52042.2 && ntc[site].value<53215.2)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.05;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>50873.2 && ntc[site].value<52042.2)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.04;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>49696.9 && ntc[site].value<50873.2)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.03;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>48646.9 && ntc[site].value<49969.6)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.02;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}


		if(ntc[site].value>47470 && ntc[site].value<48646.9)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.01;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>46530 && ntc[site].value<47470)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+0.0;		//VTSU25 = VTSU + Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>45415.9 && ntc[site].value<46530)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.01;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>44456.7 && ntc[site].value<45415.9)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.02;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>43461.8 && ntc[site].value<44456.7)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.03;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>42486.8 && ntc[site].value<43461.8)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.04;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>41602.1 && ntc[site].value<42486.8)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.05;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>40614.7 && ntc[site].value<41602.1)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.06;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>39831.9 && ntc[site].value<40614.7)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.07;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>38835.1 && ntc[site].value<39831.9)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.08;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>38146.3 && ntc[site].value<38835.1)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.09;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>37142.8 && ntc[site].value<38146.3)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.1;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>36540.8 && ntc[site].value<37142.8)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.11;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>35532.9 && ntc[site].value<36540.8)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.12;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>35011.1 && ntc[site].value<35532.9)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.13;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>34001.1 && ntc[site].value<35011.1)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.14;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>33553.4 && ntc[site].value<34001.1)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.15;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>32543.3 && ntc[site].value<33553.4)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.16;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>32164 && ntc[site].value<32543.3)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.17;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>31155.5 && ntc[site].value<32164)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.18;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>30839.2 && ntc[site].value<31155.5)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.19;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>29834 && ntc[site].value<30839.2)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value-0.20;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

		if(ntc[site].value>59860.1 && ntc[site].value<29834)	//NTC measuring value
		{
			vtsu25[site].value=vtsu[site].value+999999;		//VTSU25 = VTSU - Correlation
		    msLogResult(site, DSIndex, vtsu25[site].value);

		}

  } //main

	DSIndex=DSIndex+1;  IF_FAIL_RETURN;

    return( msSiteStat( MS_ALL ) ); // Return w/status
} // END_ETS_PRGFLOW_FUNC

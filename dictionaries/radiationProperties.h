/*--------------------------------*- C++ -*----------------------------------*\
| =========                 |                                                 |
| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
|  \\    /   O peration     | Version:  v1812                                 |
|   \\  /    A nd           | Web:      www.OpenFOAM.com                      |
|    \\/     M anipulation  |                                                 |
\*---------------------------------------------------------------------------*/
FoamFile
{
    version     2.0;
    format      ascii;
    class       dictionary;
    location    "constant";
    object      radiationProperties;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// taken from https://www.cfd-online.com/Forums/openfoam-solving/220001-icoreactingmultiphaseinterfoam-laser-dtrm.html
// courtesy navidamin

radiation       on;

radiationModel  laserDTRM;


// Number of flow iterations per radiation iteration
solverFreq 3;   // 3

absorptionEmissionModel localDensityAbsorptionEmission;

    // LPBF Parameters
    scanSpeed           0.9; // m/s
    laserPower          300; // W
    beamQuality         0.95;
    solidAbsorptivity   1.64e5;   // [1/m], 10.1063/1.3243762
    liquidAbsorptivity  1e3;
    matEmissivity       0.4; // how much the metal emission has

	mode	            "Gaussian";
	nTheta	            50;
    nr 	                20;
    maxTrackLength      0.0002;
	//opd	0.4425;
	focalLaserPosition table 	
                    (
                        (0        (.00015 .00015 0.0002))
                        (0.002    (.0018 .00015 0.0002))
                    );
	laserDirection      constant 	(0 0 -1);
	focalLaserRadius    0.000025; // 10.1038/s41467-019-10009-2
	laserPower			$laserPower;
    sigma				0.000012;
	qualityBeamLaser    $beamQuality;

    localDensityAbsorptionEmissionCoeffs
    {
    alphaNames          (alpha.gas alpha.liquid alpha.solid);
    aCoeff              (0 $liquidAbsorptivity $solidAbsorptivity);
    eCoeff              (0 0.5 $matEmissivity);
    ECoeff              (0 0.5 0.5);
    }

scatterModel            none;

sootModel               none;

transmissivityModel     none;

// ************************************************************************* //

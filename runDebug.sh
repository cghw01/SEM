#!/bin/sh
job=results
for material in Alumina Silicon
do
	echo Starting job for ${material}
	sed "s/MATERIAL/${material}/g" YieldCurve.mac > Yield${material}.mac
	gdb --args ./SEM YieldCurve.gdml Yield${material}.mac
	echo Done with job ${job} for ${material}
done

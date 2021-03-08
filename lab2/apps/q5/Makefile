default:
	cd makeprocs; make
	cd h2oinject; make
	cd h2oreact; make
	cd so4inject; make
	cd so4react; make
	cd h2so4react; make

clean:
	cd makeprocs; make clean
	cd h2oinject; make clean
	cd h2oreact; make clean
	cd so4inject; make clean
	cd so4react; make clean
	cd h2so4react; make clean

run:
	cd ../../bin; dlxsim -x os.dlx.obj -a -u makeprocs.dlx.obj 3 3; ee469_fixterminal

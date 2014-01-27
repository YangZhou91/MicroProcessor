	AREA text, CODE, READONLY
		EXPORT fermat1
fermat1
	MOV	R1, #25
	MOV R2, #75
	ADD R1, R1, R1
	BX LR;
	END
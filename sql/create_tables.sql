-- $Id: create_tables.sql,v 1.9 2002/01/18 00:04:39 nicola Exp $

CREATE SEQUENCE DOCSEQ;
CREATE SEQUENCE USERSEQ START 1000;
CREATE SEQUENCE INDIRIZZOSEQ START 100;
CREATE SEQUENCE COMUNICAZIONISEQ;
CREATE SEQUENCE MAGAZZINISEQ START 100;
CREATE SEQUENCE ARTICOLISEQ START 100;
CREATE SEQUENCE BANCHESEQ START 100;

CREATE TABLE INDIRIZZO (
	CODICE INTEGER NOT NULL DEFAULT nextval('INDIRIZZOSEQ'),
	TIPOCONTATTO SMALLINT,
	COGNOME VARCHAR(50),
	NOME VARCHAR(50),
	TITOLO VARCHAR(20),
	INDIRIZZO VARCHAR(50),
	LOCALITA VARCHAR(30),
	STATO VARCHAR(50),
	CAP VARCHAR(5),
	PROV VARCHAR(2),
	TEL VARCHAR(32),
	FAX VARCHAR(32),
	CELLULARE VARCHAR(20),
	WEB VARCHAR(255),
	EMAIL VARCHAR(100),
	PRIMARY KEY (CODICE)
);

CREATE TABLE ANAGRAFICA (
	CODICE VARCHAR(12) NOT NULL,

	RAGSOC VARCHAR(150) NOT NULL,
	TIPO VARCHAR(1),
	PARTITAIVA VARCHAR(11),
	CODICEFISCALE VARCHAR(16),

	SEDELEGALE INTEGER NOT NULL DEFAULT '0',
	SEDEAMMINISTRATIVA INTEGER NOT NULL DEFAULT '0',
	SEDEOPERATIVA INTEGER NOT NULL DEFAULT '0',

	NUMEROCONTO VARCHAR(15),
	BANCA VARCHAR(8),

	LOGO VARCHAR(255) DEFAULT 'logo',

	RITENUTA BOOLEAN,
	RICARICO DOUBLE PRECISION DEFAULT '0',

	PRIMARY KEY (CODICE)
);

CREATE TABLE DOCCLASS (
	CODICE INTEGER NOT NULL,
	MODDOC VARCHAR(1) NOT NULL,
	TIPODOC SMALLINT NOT NULL,
	ANNO INTEGER NOT NULL DEFAULT EXTRACT(YEAR FROM CURRENT_DATE),
	COUNTER INTEGER NOT NULL DEFAULT 1,
	PRIMARY KEY (CODICE)
);

CREATE TABLE ARTICOLI (
	CODICE INTEGER NOT NULL DEFAULT NEXTVAL('ARTICOLISEQ'),
	CATEGORIA SMALLINT,
	ARTICOLO VARCHAR(50),
	UM VARCHAR(15),
	CONSUMABILE BOOLEAN,
	FORNITORE VARCHAR(12),
	CODICEFORNITORE VARCHAR(20),
	COSTOUNITARIO DOUBLE PRECISION,
	IVA DOUBLE PRECISION,
	SCONTO DOUBLE PRECISION,
	DESCRIZIONE TEXT,

	PRIMARY KEY (CODICE)
);

CREATE TABLE DOCUMENTI (
	DOCPOINTER INTEGER NOT NULL DEFAULT NEXTVAL('DOCSEQ'),
	DOCCLASS INTEGER NOT NULL,
	NPROG INTEGER NOT NULL,
	SUBNUM INTEGER DEFAULT '1' NOT NULL,
	RIF VARCHAR(8),
	CODICEISO VARCHAR(24),
	DATAEMISSIONE DATE DEFAULT CURRENT_DATE,
	DATACOMPILAZIONE DATE,
	DATASCADENZA DATE,
	DATASALDO DATE,
	CLIENTE VARCHAR(12),
	FORNITORE VARCHAR(12),
	DESCRIZIONE TEXT,
	TIPOPAGAMENTO SMALLINT,
	ONERI TEXT,
	NOTE TEXT,
	OPZIONISTAMPA VARCHAR(50),

	COSTO DOUBLE PRECISION DEFAULT '0',
	IMPONIBILE DOUBLE PRECISION DEFAULT '0',
	IVA DOUBLE PRECISION DEFAULT '0',
	TOTALE DOUBLE PRECISION DEFAULT '0',
	TOTALEPAGATO DOUBLE PRECISION DEFAULT '0',
	NPEZZI INTEGER DEFAULT '0',

	DATAMODIFICA TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	DATACREAZIONE TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

	PRIMARY KEY (DOCPOINTER)
);

CREATE UNIQUE INDEX DOCCLASSPROG_SKEY ON DOCUMENTI (DOCCLASS, NPROG);

CREATE TABLE ACCONTI (
	DOCPOINTER INTEGER NOT NULL,
	ACCSEQ SMALLINT NOT NULL,	
	ACCSCAD SMALLINT NOT NULL,
	DATA DATE NOT NULL,
	IMPORTO DOUBLE PRECISION NOT NULL,
	NOTE VARCHAR(25),

	PRIMARY KEY (DOCPOINTER,ACCSEQ)
);

CREATE TABLE RIGHEDOCUMENTI (
	DOCPOINTER INTEGER NOT NULL,
	RIGA INTEGER NOT NULL,

	RIFARTICOLO INTEGER,

	COSTO DOUBLE PRECISION DEFAULT '0',
	QUANTITA DOUBLE PRECISION DEFAULT '0',
	PREZZOU DOUBLE PRECISION DEFAULT '0',
	IMPONIBILE DOUBLE PRECISION DEFAULT '0',
	IVA DOUBLE PRECISION DEFAULT '20',
	TOTALE DOUBLE PRECISION DEFAULT '0',
	NPEZZI INTEGER DEFAULT '0',

	DESCRIZIONE TEXT,
	NOTE TEXT,

	PRIMARY KEY (DOCPOINTER,RIGA)
);

CREATE TABLE ARTMAT (
	CODICEARTICOLO INTEGER NOT NULL,
	CODICEMATERIALE INTEGER NOT NULL,
	QUANTITA DOUBLE PRECISION,

	PRIMARY KEY (CODICEARTICOLO,CODICEMATERIALE)
);

CREATE TABLE BANCHE (
	CODICE VARCHAR(8) NOT NULL,
	RAGSOC VARCHAR(150) NOT NULL,
	FILIALE INTEGER NOT NULL DEFAULT '0',

	ABI VARCHAR(8),
	CAB VARCHAR(8),
	CIN VARCHAR(8),

	PRIMARY KEY (CODICE)
);

CREATE TABLE CATEGORIE (
	CODICE SMALLINT NOT NULL,
	CATEGORIA VARCHAR(40),

	PRIMARY KEY (CATEGORIA)
);

CREATE TABLE CONFIGURAZIONE (
	DITTA VARCHAR(12) NOT NULL,
	LOGO VARCHAR(255),
	VALUTA VARCHAR(10),
	FATTOREVALUTA DOUBLE PRECISION,
	RITENUTAPERC DOUBLE PRECISION,

	PRIMARY KEY (DITTA)
);

CREATE TABLE TIPIDOCUMENTI (
	CODICE SMALLINT NOT NULL,
	DESCRIZIONE VARCHAR(35) NOT NULL,

	MOSTRACLIENTE BOOLEAN,
	MOSTRAFORNITORE BOOLEAN,
	RITENUTA BOOLEAN,
	DARE BOOLEAN,
	AVERE BOOLEAN,
	SCADENZADARE BOOLEAN,
	SCADENZAAVERE BOOLEAN,
	GIORNISCADENZA INTEGER,

	PRIMARY KEY (CODICE)
);

CREATE TABLE TIPIPAGAMENTO (
	CODICE SMALLINT NOT NULL,
	DESCRIZIONE VARCHAR(150),

	PRIMARY KEY (CODICE)
);

CREATE TABLE DOCUMENTICONSEGNA (
	DOCPOINTER INTEGER NOT NULL,
	LUOGOCONSEGNA VARCHAR(35),
	TERMINICONSEGNA VARCHAR(35),
	VOSTRORIF VARCHAR(35),
	CONTATTO VARCHAR(35),
	TRASPMEZZO VARCHAR(20),
	ACARICO VARCHAR(20),
	RESAFRANCO VARCHAR(20),
	IMBALLO VARCHAR(30),
	APPROVVIGIONAMENTO VARCHAR(25),
	RICHCERTIFICATO VARCHAR(25),

	PRIMARY KEY(DOCPOINTER)
);

CREATE TABLE MAGAZZINI (
	CODICE SMALLINT NOT NULL DEFAULT nextval('MAGAZZINISEQ'),
	NOME VARCHAR(30),
	DESCRIZIONE TEXT,
	NOTE TEXT,
	
	LOCAZIONE INTEGER,

	DATAAPERTURA DATE,
	DATACHIUSURA DATE,

	BLOCCATO BOOLEAN,

	PRIMARY KEY (CODICE)
);

CREATE TABLE ONERI (
	CODICE VARCHAR(4) NOT NULL,
	BRIEFDESC VARCHAR(50),
	DESCRIZIONE TEXT,

	PRIMARY KEY (CODICE)
);

CREATE TABLE SCORTE (
	MAGAZZINO SMALLINT NOT NULL DEFAULT '0',
	ARTICOLO INTEGER NOT NULL,
	QUANTITA DOUBLE PRECISION,
	PRENOTAZIONE DOUBLE PRECISION,
	PRIMARY KEY (MAGAZZINO,ARTICOLO)
);


CREATE TABLE TIPICONTATTI (
	TIPOCONTATTO INTEGER NOT NULL,
	CONTATTO VARCHAR(35),

	PRIMARY KEY (TIPOCONTATTO)
);


CREATE TABLE MENU (
	MENUID INTEGER NOT NULL,
	NODEID VARCHAR(50) NOT NULL,
	LEVEL INTEGER NOT NULL,
	ORDER_NUM INTEGER NOT NULL,
	LINK VARCHAR(30) NOT NULL,
	SHORTLINK VARCHAR(30),
	CONTENT VARCHAR(100) NOT NULL,
	DESCRIPTION VARCHAR(100) NOT NULL,
	DYNAMIC VARCHAR(255),
	STATIC VARCHAR(255),	
	ENABLED BOOLEAN DEFAULT 'TRUE',
	REQUIRES VARCHAR(255) NOT NULL DEFAULT '.*',
	HELP TEXT,

	PRIMARY KEY (MENUID)
);


CREATE TABLE UTENTI (
	USERID INTEGER NOT NULL DEFAULT NEXTVAL('USERSEQ'),
	USERNAME VARCHAR(32) NOT NULL DEFAULT '',
	PASSWORD VARCHAR(32) NOT NULL DEFAULT '*',
	DESCRIZIONE VARCHAR(50),
	PERMESSI TEXT DEFAULT '.*',

	PRIMARY KEY(USERID)
);

CREATE UNIQUE INDEX UTENTIUSERNAME_SKEY ON UTENTI (USERNAME);


CREATE VIEW VIEW_DOCCLASS as
	SELECT D.CODICE as CODICE, D.MODDOC as MODDOC, D.ANNO as ANNO, D.TIPODOC as TIPODOC,
			    T.DESCRIZIONE as DESCRIZIONE, T.MOSTRACLIENTE as MOSTRACLIENTE, T.MOSTRAFORNITORE as MOSTRAFORNITORE,
			    T.RITENUTA as RITENUTA, D.COUNTER as PROSSIMO
			    FROM DOCCLASS D,TIPIDOCUMENTI T 
 			    WHERE D.TIPODOC=T.CODICE;


CREATE VIEW VIEW_DOCUMENTI as
	SELECT d.*,d.iva as ivaimporto, c.anno as anno, c.prossimo as prossimo,
	c.moddoc as moddoc, c.descrizione as tipodescr,
	c.tipodoc as tipodoc, c.ritenuta as ritenuta, c.mostracliente as mostracliente,
	c.mostrafornitore as mostrafornitore
	FROM documenti d,view_docclass c
	where d.docclass=c.codice;



CREATE VIEW VIEW_ANAGRAFICA AS
	SELECT  A.CODICE AS CODICE, A.RAGSOC AS RAGSOC, 
		A.PARTITAIVA AS PARTITAIVA, A.CODICEFISCALE AS CODICEFISCALE, 
		A.NUMEROCONTO as NUMEROCONTO, A.BANCA as BANCA, A.RICARICO as RICARICO,
		B.NOME AS NOMELEGALE, B.COGNOME AS COGNOMELEGALE, B.INDIRIZZO AS INDIRIZZOLEGALE,
		  B.LOCALITA as LOCALITALEGALE, B.STATO as STATOLEGALE, B.CAP as CAPLEGALE,
		  B.PROV as PROVLEGALE, B.TEL as TELLEGALE, B.FAX as FAXLEGALE, B.CELLULARE as CELLULARELEGALE,
		  B.WEB as WEBLEGALE, B.EMAIL as EMAILLEGALE,
		C.NOME AS NOMEAMM,    C.COGNOME AS COGNOMEAMM,    C.INDIRIZZO AS INDIRIZZOAMM,
		  C.LOCALITA as LOCALITAAMM, C.STATO as STATOAMM, C.CAP as CAPAMM,
		  C.PROV as PROVAMM, C.TEL as TELAMM, C.FAX as FAXAMM, C.CELLULARE as CELLULAREAMM,
		  C.WEB as WEBAMM, C.EMAIL as EMAILAMM
	FROM 
		ANAGRAFICA A, INDIRIZZO B, INDIRIZZO C 
	WHERE 
		B.CODICE=A.SEDELEGALE AND 
		C.CODICE=A.SEDEAMMINISTRATIVA;

CREATE VIEW VIEW_BANCHE AS
	SELECT A.CODICE as CODICE, A.RAGSOC as RAGSOC, A.ABI as ABI, A.CAB as CAB, A.CIN as CIN,
		B.NOME AS NOMELEGALE, B.COGNOME AS COGNOMELEGALE, B.INDIRIZZO AS INDIRIZZOLEGALE,
		  B.LOCALITA as LOCALITALEGALE, B.STATO as STATOLEGALE, B.CAP as CAPLEGALE,
		  B.PROV as PROVLEGALE, B.TEL as TELLEGALE, B.FAX as FAXLEGALE, B.CELLULARE as CELLULARELEGALE,
		  B.WEB as WEBLEGALE, B.EMAIL as EMAILLEGALE
	FROM
		BANCHE A, INDIRIZZO B
	WHERE
		B.CODICE=A.FILIALE;


CREATE VIEW VIEW_MAGAZZINI AS
	SELECT A.CODICE as CODICE, A.NOME as NOME, A.DESCRIZIONE as DESCRIZIONE, A.NOTE as NOTE,
		A.DATAAPERTURA as DATAAPERTURA, A.DATACHIUSURA as DATACHIUSURA,
		A.BLOCCATO as BLOCCATO,
	
		B.INDIRIZZO AS INDIRIZZO,
		B.LOCALITA as LOCALITA, B.STATO as STATO, B.CAP as CAP,
		B.PROV as PROV, B.TEL as TEL
	FROM
		MAGAZZINI A, INDIRIZZO B
	WHERE
		B.CODICE=A.LOCAZIONE;

create view VIEW_RIGHE AS
	SELECT R.DOCPOINTER, R.RIGA as RIGA, R.RIFARTICOLO as RIFARTICOLO, R.COSTO as COSTO, R.QUANTITA as QUANTITA, 
	       R.PREZZOU as PREZZOU, R.IMPONIBILE as IMPONIBILE, R.IVA as IVA, (R.IVA/100) * R.IMPONIBILE as IVAIMPORTO,
	       R.TOTALE as TOTALE, R.NPEZZI as NPEZZI, 
	       R.DESCRIZIONE as DESCRIZIONE, R.NOTE as NOTE,
	       A.UM as UM, A.CATEGORIA as CATEGORIA, A.ARTICOLO as ARTICOLO, A.COSTOUNITARIO as A_COSTO, A.IVA as A_IVA, A.DESCRIZIONE as A_DESCRIZIONE
	       FROM RIGHEDOCUMENTI R LEFT OUTER JOIN ARTICOLI A ON R.RIFARTICOLO=A.CODICE
	       ORDER BY R.riga;

create view VIEW_ARTICOLI as
	SELECT A.*, C.CATEGORIA as CATEGORIADESCR from ARTICOLI A, CATEGORIE C
	where A.CATEGORIA=C.CODICE;

CREATE view LIST_ARTICOLI as
	select CODICE, ARTICOLO, CATEGORIADESCR, DESCRIZIONE, FORNITORE
	from VIEW_ARTICOLI;

CREATE VIEW LIST_ANAGRAFICA AS
	SELECT CODICE, RAGSOC, PARTITAIVA, CODICEFISCALE from ANAGRAFICA;

CREATE VIEW LIST_MAGAZZINI AS
	SELECT CODICE, NOME, DESCRIZIONE, LOCALITA, PROV, BLOCCATO from VIEW_MAGAZZINI;

CREATE VIEW LIST_BANCHE AS
	SELECT CODICE, RAGSOC, ABI, CAB from BANCHE;

CREATE VIEW LIST_UTENTI AS
	SELECT USERID, USERNAME, DESCRIZIONE from UTENTI;

CREATE USER EUROFATTU WITH PASSWORD 'EUROFATTU';

GRANT
	 SELECT, INSERT, DELETE, UPDATE
ON
	 ACCONTI,
	 ANAGRAFICA,
	 ARTICOLI,
	 ARTMAT,
	 BANCHE,
	 CATEGORIE,
	 CONFIGURAZIONE,
	 DOCCLASS,
	 DOCUMENTI,
	 DOCUMENTICONSEGNA,
	 INDIRIZZO,
	 MAGAZZINI,
	 ONERI,
	 RIGHEDOCUMENTI,
	 SCORTE,
	 TIPICONTATTI,
	 TIPIDOCUMENTI,
	 TIPIPAGAMENTO
TO 
	 EUROFATTU;

GRANT
	 SELECT
ON
	 VIEW_ANAGRAFICA, VIEW_DOCUMENTI, VIEW_BANCHE, VIEW_DOCCLASS,
	 LIST_ANAGRAFICA, LIST_BANCHE, LIST_MAGAZZINI, LIST_ARTICOLI
TO
  	 EUROFATTU;
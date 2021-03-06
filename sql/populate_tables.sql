TRUNCATE TABLE MAGAZZINI;
TRUNCATE TABLE TIPIDOCUMENTI;
TRUNCATE TABLE DOCCLASS;
TRUNCATE TABLE UTENTI;
TRUNCATE TABLE MENU;
TRUNCATE TABLE ANAGRAFICA;
TRUNCATE TABLE ARTICOLI;

BEGIN TRANSACTION;

INSERT INTO MAGAZZINI (CODICE, NOME) VALUES(0,'Sede centrale');

INSERT INTO TIPIDOCUMENTI (CODICE, DESCRIZIONE, MOSTRACLIENTE, MOSTRAFORNITORE, RITENUTA, DARE, AVERE, SCADENZADARE, SCADENZAAVERE, GIORNISCADENZA) values (1,  'Fattura', TRUE , FALSE , FALSE ,FALSE, TRUE, FALSE, TRUE,  15);
INSERT INTO TIPIDOCUMENTI (CODICE, DESCRIZIONE, MOSTRACLIENTE, MOSTRAFORNITORE, RITENUTA, DARE, AVERE, SCADENZADARE, SCADENZAAVERE, GIORNISCADENZA) values (2,  'Contratto', TRUE , FALSE , FALSE ,FALSE, TRUE, FALSE, TRUE,  15);
INSERT INTO TIPIDOCUMENTI (CODICE, DESCRIZIONE, MOSTRACLIENTE, MOSTRAFORNITORE, RITENUTA, DARE, AVERE, SCADENZADARE, SCADENZAAVERE, GIORNISCADENZA) values (3,  'Preventivo',TRUE , FALSE , FALSE ,FALSE, TRUE, FALSE, TRUE,  15);
INSERT INTO TIPIDOCUMENTI (CODICE, DESCRIZIONE, MOSTRACLIENTE, MOSTRAFORNITORE, RITENUTA, DARE, AVERE, SCADENZADARE, SCADENZAAVERE, GIORNISCADENZA) values (4,  'Commessa', TRUE , FALSE , FALSE ,FALSE, TRUE, FALSE, TRUE,  15);
INSERT INTO TIPIDOCUMENTI (CODICE, DESCRIZIONE, MOSTRACLIENTE, MOSTRAFORNITORE, RITENUTA, DARE, AVERE, SCADENZADARE, SCADENZAAVERE, GIORNISCADENZA) values (5,  'Registrazione', FALSE , TRUE , FALSE ,TRUE, FALSE, TRUE , FALSE,  15);
INSERT INTO TIPIDOCUMENTI (CODICE, DESCRIZIONE, MOSTRACLIENTE, MOSTRAFORNITORE, RITENUTA, DARE, AVERE, SCADENZADARE, SCADENZAAVERE, GIORNISCADENZA) values (6,  'DDT', TRUE , TRUE , FALSE ,FALSE, FALSE, FALSE, FALSE,  0);

INSERT INTO DOCCLASS (CODICE, MODDOC, TIPODOC,ANNO) VALUES (120020001,'D',1,2002);
INSERT INTO DOCCLASS (CODICE, MODDOC, TIPODOC,ANNO) VALUES (120020002,'D',2,2002);
INSERT INTO DOCCLASS (CODICE, MODDOC, TIPODOC,ANNO) VALUES (120020003,'D',3,2002);
INSERT INTO DOCCLASS (CODICE, MODDOC, TIPODOC,ANNO) VALUES (120020004,'D',4,2002);
INSERT INTO DOCCLASS (CODICE, MODDOC, TIPODOC,ANNO) VALUES (120020005,'D',5,2002);
INSERT INTO DOCCLASS (CODICE, MODDOC, TIPODOC,ANNO) VALUES (120020006,'D',6,2002);
INSERT INTO DOCCLASS (CODICE, MODDOC, TIPODOC) VALUES (200010001,'M',1);
INSERT INTO DOCCLASS (CODICE, MODDOC, TIPODOC) VALUES (200010002,'M',2);
INSERT INTO DOCCLASS (CODICE, MODDOC, TIPODOC) VALUES (200010003,'M',3);
INSERT INTO DOCCLASS (CODICE, MODDOC, TIPODOC) VALUES (200010004,'M',4);
INSERT INTO DOCCLASS (CODICE, MODDOC, TIPODOC) VALUES (200010005,'M',5);
INSERT INTO DOCCLASS (CODICE, MODDOC, TIPODOC) VALUES (200010006,'M',6);

INSERT INTO UTENTI (USERID, USERNAME, PASSWORD, DESCRIZIONE, PERMESSI) VALUES (1, 'admin', 'admin','Administrator','Rf,Wf,Rp,Wp,Ra,Wa,Ru,Wu,Rb,Wb');

INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (00000,'ID_MAIN', 1, 10000,'Indice',NULL,'','','main');

INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC, REQUIRES) VALUES (10100,'ID_FATTURE_ELENCO', 2, 30000,'Fatture',NULL,'','','doc_edit','Rf');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC, REQUIRES) VALUES (10110,'ID_FATTURE_VISUALIZZA', 3, 31000,'Visualizza fattura','Visualizza','','','doc_edit','Rf');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC, REQUIRES) VALUES (10120,'ID_FATTURE_CREA', 3, 32000,'Nuova fattura','Nuova','','','doc_edit','Wf');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC, REQUIRES) VALUES (10130,'ID_FATTURE_CAMBIA', 3, 33000,'Modifica fattura','Modifica','','','doc_edit','Wf');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC, REQUIRES) VALUES (10140,'ID_FATTURE_DOWNLOAD',   3, 33500,'Download','Download','','','doc_edit','Rf');

INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (10200,'ID_PREVENTIVI_ELENCO', 2, 40000,'Preventivi',NULL,'','','doc_edit');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (10201,'ID_PREVENTIVI_VISUALIZZA', 3, 41000,'Visualizza preventivi','Visualizza','','','doc_edit');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (10202,'ID_PREVENTIVI_CREA', 3, 42000,'Nuovo preventivo','Nuovo','','','doc_edit');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (10203,'ID_PREVENTIVI_CAMBIA', 3, 43000,'Modifica preventivo','Modifica','','','doc_edit');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (10240,'ID_PREVENTIVI_DOWNLOAD', 3, 44000,'Download','Download','','','doc_edit');

INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (20100,'ID_ANAGRAFICA_ELENCO', 2, 80000,'Anagrafica',NULL,'','','personaldata');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (20200,'ID_ANAGRAFICA_VISUALIZZA', 3, 81000,'Visualizza anagrafica','Visualizza','','','personaldata');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (20300,'ID_ANAGRAFICA_CREA', 3, 82000,'Nuova anagrafica','Nuova','','','personaldata');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (20400,'ID_ANAGRAFICA_ELIMINA', 3, 83000,'Elimina anagrafica','Elimina','','','personaldata');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (20500,'ID_ANAGRAFICA_CAMBIA', 3, 84000,'Modifica anagrafica','Modifica','','','personaldata');

INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (21100,'ID_BANCHE_ELENCO', 2, 85000,'Banche',NULL,'','','banks');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (21200,'ID_BANCHE_VISUALIZZA', 3, 86000,'Visualizza banca','Visualizza','','','banks');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (21300,'ID_BANCHE_CREA', 3, 87000,'Nuova banca','Nuova','','','banks');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (21400,'ID_BANCHE_ELIMINA', 3, 88000,'Elimina banca','Elimina','','','banks');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (21500,'ID_BANCHE_CAMBIA', 3, 89000,'Modifica banca','Modifica','','','banks');

INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (22100,'ID_ARTICOLI_ELENCO', 2, 90000,'Articoli',NULL,'','','items');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (22200,'ID_ARTICOLI_VISUALIZZA', 3, 91000,'Visualizza articolo','Visualizza','','','items');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (22300,'ID_ARTICOLI_CREA', 3, 92000,'Nuovo articolo','Nuovo','','','items');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (22400,'ID_ARTICOLI_ELIMINA', 3, 93000,'Elimina articolo','Elimina','','','items');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (22500,'ID_ARTICOLI_CAMBIA', 3, 94000,'Modifica articolo','Modifica','','','items');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (22600,'ID_CATEGORIE_CAMBIA', 3, 94500,'Categorie articoli','Categorie','','','categories');

INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (30100,'ID_UTENTI_ELENCO', 2, 95000,'Gestione utenti','Utenti','','','users');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (30200,'ID_UTENTI_CREA', 3,100000,'Nuovo utente','Nuovo','','','users');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (30300,'ID_UTENTI_ELIMINA', 3,110000,'Cancella utente','Cancella','','','users');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (30400,'ID_UTENTI_CAMBIA', 3,120000,'Cambia dati utente','Modifica','','','users');

INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (40000,'ID_INFO', 2,130100,'Info',NULL,'','','');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (41000,'ID_INFO_ABOUT', 3,130200,'About',NULL,'','','');
INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, STATIC) VALUES  (42000,'ID_INFO_LICENZA', 3,130300,'Licenza',NULL,'','','.license');

INSERT INTO MENU (MENUID, NODEID, LEVEL, ORDER_NUM, LINK, SHORTLINK, CONTENT, DESCRIPTION, DYNAMIC) VALUES (50000,'ID_LOGOUT', 2,140000,'Esci',NULL,'','','logout');

INSERT INTO INDIRIZZO (CODICE) VALUES(0);
INSERT INTO INDIRIZZO (CODICE, CAP, INDIRIZZO, LOCALITA, PROV, WEB, EMAIL) values
 (1, '09047','Via S.Ignazio, 18','Selargius','CA','www.dotsrl.com','dot@dotsrl.com');
INSERT INTO INDIRIZZO (CODICE, CAP, INDIRIZZO, LOCALITA, PROV, WEB, EMAIL) values
 (2,'09042','Via Monte Arci, 44bis','Monserrato', 'CA','www.dotsrl.com','dot@dotsrl.com');
INSERT INTO ANAGRAFICA (CODICE, RAGSOC,SEDELEGALE,SEDEAMMINISTRATIVA,PARTITAIVA) 
 VALUES ('1', 'Dot S.r.l', 1, 2,'02448300927');

INSERT INTO CATEGORIE (CODICE, CATEGORIA) VALUES
 (1,'Servizi');
INSERT INTO CATEGORIE (CODICE, CATEGORIA) VALUES
 (2,'Prodotti');
INSERT INTO CATEGORIE (CODICE, CATEGORIA) VALUES
 (3,'Sconti e promozioni');

INSERT INTO ARTICOLI (CODICE, CATEGORIA, ARTICOLO, UM, COSTOUNITARIO,IVA) VALUES 
 (1,1,'Servizio','Corpo',1.0,20.0);

COMMIT;
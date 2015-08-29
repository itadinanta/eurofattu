<?php //$Id: document.inc,v 1.3 2002/01/18 00:02:23 nicola Exp $
    include_once("sqlcmd.inc");
include_once("debug.inc");

class ef_document {
    var $DOC_HEADER,
	$DOC_ROWS;
    function ef_document($DOCPOINTER) {
	$this->docpointer=$DOCPOINTER;
    }
    function collect_form_data($form_variables) {
	$fields=array("codiceiso","dataemissione","cliente","fornitore",
		      "descrizione","tipopagamento","oneri","note");
	$fd_doc=$form_variables["fd_doc"];
	DEBUG($fd_doc,"fd_doc");
	foreach($fields as $field) $this->DOC_HEADER[$field]=$fd_doc[$field];
	$fields_rows=array("riga","rifarticolo","quantita","prezzou","descrizione","iva","note");
	$fd_doc_rows=$form_variables["fd_doc_row"];
	$fd_doc_row_oldpos=$form_variables["fd_doc_row_oldpos"];
	$fd_doc_row_newpos=$form_variables["fd_doc_row_newpos"];
	$this->DOC_ROWS=array();

	/* Inizializza slots */
	$poscount=count($fd_doc_row_newpos);
	for($i=1; $i<=$poscount;$i++) $slot[$i]=0;

	/* Assegna posizioni alle righe che cambiano posto */
	foreach ($fd_doc_row_newpos as $i=>$newpos) {
	    $oldpos=$fd_doc_row_oldpos[$i];
	    if (!$oldpos) $oldpos=$poscount;
	    if ($oldpos != $newpos && $newpos) {
		$freepos=$newpos;
		while ($slot[$freepos]) $freepos++;
		$slot[$freepos]=$oldpos;
	    }
	}

	/* Assegna posizioni alle righe che non si spostano*/
	$freepos=1;
	foreach ($fd_doc_row_newpos as $i=>$newpos) {
	    $oldpos=$fd_doc_row_oldpos[$i];
	    if (!$oldpos) $oldpos=$poscount;
	    if ($oldpos == $newpos) {
		while ($slot[$freepos]) $freepos++;
		$slot[$freepos]=$oldpos;
	    }
	}
	DEBUG($slot,"SLOT");

	foreach($fd_doc_rows as $i=>$valid) if ($valid) {

	    if ($slot[$i+1]) {
		$row_n=$slot[$i+1]-1;
		foreach($fields_rows as $field) 
		    $row[$field]=$form_variables["fd_doc_row_item_$field"][$row_n];
		
		if ($row["rifarticolo"] || $row["quantita"]) {
		    $this->DOC_ROWS[$nr]=$row;
		    $this->DOC_ROWS[$nr]["riga"]=$nr+1;
		    $this->DOC_ROWS[$nr]["docpointer"]=$this->docpointer;
		    $this->fill_row($this->DOC_ROWS[$nr]);
		    DEBUG($this->DOC_ROWS[$nr],"COLLECTED_ROW $nr");
		    $nr++;
		}
	    }
	}
    }
    function compute() {
	$this->DOC_HEADER["totale"]=0;
	$this->DOC_HEADER["imponibile"]=0;
	$this->DOC_HEADER["iva"]=0;
	$this->DOC_HEADER["costo"]=0;
	foreach($this->DOC_ROWS as $key=>$row) {
	    $this->fill_row($row);
	    $row["imponibile"]=$row["prezzou"]*$row["quantita"];
	    $row["totale"]=$row["imponibile"]*(1.0+$row["iva"]/100.0);
	    $costo=$row["costo"]=$row["quantita"];
	    $this->DOC_HEADER["totale"]+=$row["totale"];
	    $this->DOC_HEADER["imponibile"]+=$row["imponibile"];
	    $this->DOC_HEADER["iva"]+=$row["imponibile"]*($row["iva"]/100.0);
	    $this->DOC_HEADER["costo"]+=$row["costo"];
	    $this->DOC_ROWS[$key]=$row;
	}
    }
    function create($docclass) {
	if ($this->docpointer) return;
	$creation_result=ef_q_create_document($docclass);
	$this->docpointer=$creation_result["docpointer"];
	return $this->docpointer;
    }
    function load() {
	if (!$this->docpointer) return;
	$this->DOC_HEADER=ef_q_get_document($this->docpointer);
	$this->DOC_ROWS=ef_q_get_document_rows($this->docpointer);
    }
    function save() {
	ef_q_save_document($this->DOC_HEADER, $this->DOC_ROWS);
    }

    function fill_row(&$ROW) {
	if ($ROW["rifarticolo"]) {
	    if ($ROW["iva"]=="") $ROW["iva"]=$ROW["a_iva"];
	    if ($ROW["descrizione"]=="") $ROW["descrizione"]=$ROW["a_descrizione"];
	    if ($ROW["costo"]=="") $ROW["costo"]=$ROW["a_costo"];

	    $ART=ef_q_item($ROW["rifarticolo"]);

	    if ($ROW["iva"]=="") $ROW["iva"]=$ART["iva"];
	    if ($ROW["descrizione"]=="") $ROW["descrizione"]=$ART["descrizione"];
	    if ($ROW["costo"]=="") $ROW["costo"]=$ART["costounitario"];
	    if ($ROW["prezzou"]=="") $ROW["prezzou"]=$ART["costounitario"]*(1.0+CONFIG(OVERPRICE)/100.0);
	    $ROW["um"]=$ART["um"];
	}
    }
}
?>

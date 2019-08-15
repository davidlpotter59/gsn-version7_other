/* summary_detail_alae.eq

   SCIPS.com

   December 9, 2004

   show where summary and detail are out of balance for ALAE resv and ALAE paid
*/

description Report to show where summary and detail are out of balance for ALAE resv and ALAE paid ;
  
define file lrsdetaila = access lrsdetail, 

set lrsdetail:company_id = lrssummary:company_id,

    lrsdetail:claim_no   = lrssummary:claim_no, one to many, generic 

define signed ascii number l_alae_paid = if
((lrsdetaila:trans_code < 30 or
lrsdetaila:trans_code > 89) and 
lrsdetaila:alae = "Y" and
(lrsdetaila:summary_sub_code = lrssummary:sub_code or
(lrsdetaila:summary_sub_code = 0 and
lrssummary:sub_code = 10)))

then lrsdetaila:lae_paid 

else 0.00
 
define signed ascii number l_alae_resv = if
((lrsdetaila:trans_code < 30 or
lrsdetaila:trans_code > 89) and 
lrsdetaila:alae = "Y" and
(lrsdetaila:summary_sub_code = lrssummary:sub_code or
(lrsdetaila:summary_sub_code = 0 and
lrssummary:sub_code = 10)))

then lrsdetaila:lae_resv 

else 0.00   
list

/nobanner

/domain="lrssummary"

/nodetail 

/title="Summary to Detail Balance Issues - ALAE"

/nototals 

/pagelength=0

/pagewidth=255   

 

lrssummary:claim_no/column=1

lrssummary:alae_resv/heading="Lrssummary-ALAE Resv"
L_alae_resv/heading="Lrsdetail-ALAE Resv"

lrssummary:alae_paid/heading="Lrssummary-ALAE Paid'"
L_alae_paid/heading="Lrsdetail-ALAE Paid"


 

sorted by lrssummary:claim_no 

                                               
end of report
   total[lrssummary:alae_resv]/column=10

   total[l_alae_resv]/column=30

   total[lrssummary:alae_paid]/column=50

   total[l_alae_paid]/column=70   
         
end of lrssummary:claim_no 

box/noblanklines/noheadings 

if total[lrssummary:alae_resv ] <> total[l_alae_resv] or 

   total[lrssummary:alae_paid]  <> total[l_alae_paid] then 

{

   lrssummary:claim_no /column=1

   total[lrssummary:alae_resv]/column=10

   total[l_alae_resv]/column=30

   total[lrssummary:alae_paid]/column=50

   total[l_alae_paid]/column=70                      
 

   if total[lrssummary:alae_resv] <> total[l_alae_resv] then 

   {

     "Reserves out of balance"/column=100

   }

   if total[lrssummary:alae_paid] <> total[l_alae_paid] then 

   {

     "Payments out of balance"/column=130

   }

 

}

end box

 

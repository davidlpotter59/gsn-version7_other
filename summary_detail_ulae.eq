/* summary_detail_ulae.eq

   SCIPS.com

   December 9, 2004

   show where summary and detail are out of balance for ULAE resv and ULAE paid
*/

description Report to show where summary and detail are out of balance for ULAE resv and ULAE paid ;
  
define file lrsdetaila = access lrsdetail, 

set lrsdetail:company_id = lrssummary:company_id,

    lrsdetail:claim_no   = lrssummary:claim_no, one to many, generic 



define signed ascii number l_ulae_paid = if
((lrsdetaila:trans_code < 30 or
lrsdetaila:trans_code > 89) and 
lrsdetaila:ulae = "Y" and
(lrsdetaila:summary_sub_code = lrssummary:sub_code or
(lrsdetaila:summary_sub_code = 0 and
lrssummary:sub_code = 10)))

then lrsdetaila:lae_paid 

else 0.00
 
define signed ascii number l_ulae_resv = if
((lrsdetaila:trans_code < 30 or
lrsdetaila:trans_code > 89) and 
lrsdetaila:ulae = "Y" and
(lrsdetaila:summary_sub_code = lrssummary:sub_code or
(lrsdetaila:summary_sub_code = 0 and
lrssummary:sub_code = 10)))

then lrsdetaila:lae_resv 

else 0.00     

list

/nobanner

/domain="lrssummary"

/nodetail 

/title="Summary to Detail Balance Issues - ULAE"

/nototals 

/pagelength=0

/pagewidth=255   

 

lrssummary:claim_no/column=1

lrssummary:ulae_resv/heading="Lrssummary-ULAE Resv"
l_ulae_resv/heading="Lrsdetail-ULAE Resv"

lrssummary:ulae_paid/heading="Lrssummary-ULAE Paid'"
l_ulae_paid/heading="Lrsdetail-ULAE Paid"   
 

sorted by lrssummary:claim_no 

 
end of report
total[lrssummary:ulae_resv]/column=10

   total[l_ulae_resv]/column=30

   total[lrssummary:ulae_paid]/column=50

   total[l_ulae_paid]/column=70                      

end of lrssummary:claim_no 

box/noblanklines/noheadings 

if total[lrssummary:ulae_resv ] <> total[l_ulae_resv] or 

   total[lrssummary:ulae_paid]  <> total[l_ulae_paid] then 

{

   lrssummary:claim_no /column=1

   total[lrssummary:ulae_resv]/column=10

   total[l_ulae_resv]/column=30

   total[lrssummary:ulae_paid]/column=50

   total[l_ulae_paid]/column=70                      
 

   if total[lrssummary:ulae_resv] <> total[l_ulae_resv] then 

   {

     "Reserves out of balance"/column=100

   }

   if total[lrssummary:ulae_paid] <> total[l_ulae_paid] then 

   {

     "Payments out of balance"/column=130

   }

 

}

end box

 

#include <payment/paymentcgi.h>
#include <mgr/mgrrpc.h>
#include <mgr/mgrdate.h>
#include <mgr/mgrhash.h>
#include <mgr/mgrstream.h>
#include <sstream>
 
MODULE("valenockpayment");

using namespace payment;

class valenockPayment : public PaymentCgi {
public:
	valenockPayment() : PaymentCgi("valenock", "valenockpayment")
	{
		
	}
	
	virtual bool ValidateAuth() {
		return true;
	}
	
	virtual void Process() {
		StringMap payment_form_param;
		payment_form_param["merchant_id"] = Method("vl_merchant_id");
		payment_form_param["payment_amount"] = Payment("amount");
		payment_form_param["payment_desc"] = Payment("description");
		payment_form_param["payment_id"] = Payment("id");
		
		string token = str::base64::Encode(str::hex::Encode(mgr_hash::sha1(Payment("amount")+"|"+Payment("id")+"|"+Method("vl_merchant_id")+"|"+Method("vl_secret_key")))); 
		string form_str = "<html>\n"
						"<head>"
						"	<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'/>\n"
						"	<link rel='shortcut icon' href='https://valenock.ru/img/valenock-small-logo.png' type='image/x-icon'/>\n"
						"	<script language='JavaScript'>\n"
						"		function DoSubmit() {\n"
						"			document.valenockform.submit();\n"
						"		}\n"
						"	</script>\n"
						"</head>\n"
						"<body onload='DoSubmit()'>\n"
						"	<form name='valenockform' action='https://pay.valenock.ru/' method='post' accept-charset='utf8'>\n";
		
		ForEachI(payment_form_param, p) {
			str::inpl::Append(form_str, 
						"		<input type='hidden' name='" + p->first + "' value='" + p->second + "'>", "\n");
		}

		form_str +=					
						"		<input type='hidden' name='token' value='" + token + "'>\n"
						"	</form>\n"
						"</body>\n"
						"</html>\n";
		
		std::cout << form_str;
	}
};

RUN_MODULE(valenockPayment)

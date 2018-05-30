#include <payment/paymentcgi.h>
#include <mgr/mgrrpc.h>
#include <mgr/mgrdate.h>
#include <mgr/mgrstream.h>
#include <payment/paymentutil.h>
#include <mgr/mgrhash.h>
#include <sstream>

MODULE("valenockresult");

using namespace payment;

class valenockResult : public PaymentCgi {
public:
	valenockResult() : PaymentCgi("valenock", "valenockresult")
	{
		
	}
	
	//virtual string ContentType() 
	//{
	//	return "text/xml";
	//}
	
	virtual string ElidParam() 
	{
		return "payment_id";
	}
	
	virtual bool ValidateAuth() {
		return false;
	}
	
	
	virtual void Process() {
		if (Input("merchant_id") != Method("vl_merchant_id")) {
			throw mgr_err::Error("unknow_provider");
		}
		
		if (Input("payment_amount") != Payment("amount")) {
			throw mgr_err::Value("amonut");
		}
		
		if (Input("status") == "success") {
			string signature = Input("signature");
			string sign_str =
			Input("status")+"|"+
			Input("payment_amount")+"|"+
			Input("payment_id")+"|"+
			Input("vl_merchant_id")+"|"+
			Method("vl_secret_key");
			
			string sign = str::base64::Encode(str::hex::Encode(mgr_hash::sha1(
				Input("status")+"|"+Input("payment_amount")+"|"+Input("payment_id")+"|"+Input("merchant_id")+"|"+Method("vl_secret_key")
			))); 
			
			if (signature != sign) {
				throw mgr_err::Value("signature");
			}else{
				SetPaid(Input("payment_id"));
			}
		
		}
	}
};

RUN_MODULE(valenockResult)

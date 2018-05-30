#include <billmgr/payment/paymentmodule.h>

using namespace payment;

#define BINARY_NAME "pmvalenock"

class valenock : public Module {
public:
	valenock() : Module("valenock", "1.0")
	{
		feature_map[PAYMENT_FEATURE_REDIRECT] = true;
		feature_map[PAYMENT_FEATURE_NOT_PROFILE] = true;

		param_map[PAYMENT_PARAM_PAYMENT_SCRIPT] = "/mancgi/valenockpayment";
	}
};

RUN_MODULE(valenock)


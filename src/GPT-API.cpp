#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include "httplib.h"
#include "json.hpp"
using namespace std;

using json = nlohmann::json;

class GptBaiduApiClient {
public:
	GptBaiduApiClient(const std::string& clientId, const std::string& clientSecret, const std::string& gptServerUrl="")
		: clientId(clientId), clientSecret(clientSecret), gptServerUrl(gptServerUrl) {}

	// ��ȡBaidu Access Token
	std::string getAccessToken() {
		httplib::Client client("https://aip.baidubce.com");

		httplib::Params params;
		httplib::Headers headers;
		params.emplace("client_id", clientId);
		params.emplace("client_secret", clientSecret);
		params.emplace("grant_type", "client_credentials");
		headers.emplace("Content-Type", "application/json");

		auto response = client.Post("/oauth/2.0/token", headers, params);

		if (response && response->status == 200) {
			json jsonResponse = json::parse(response->body);
			string accessToken = jsonResponse["access_token"];
			return accessToken;
		}
		else {
			return "Error getting Baidu Access Token.";
		}
	}

    std::string getinGPT(const std::string& userMessage) {
        httplib::Client client("https://aip.baidubce.com");

        httplib::Params params;
        httplib::Headers headers;

        std::string accessToken = getAccessToken();

        headers.emplace("Content-Type", "application/json");
        params.emplace("access_token", accessToken);

        json body = {
            {"messages", json::array({
                {
                    {"role", "user"},
                    {"content", userMessage}
                }
            })}
        };

        std::string bodyString = body.dump();

        // ���� HTTP ����
        auto response = client.Post("/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/completions_pro?access_token=" + accessToken, bodyString, "application/json");

        if (response && response->status == 200) {
            json gptOutput = json::parse(response->body);
            std::string responseContent = gptOutput["result"];
            return responseContent;
        }
        else {
            return "Error in GPT request.";
        }
    }    

private:
	std::string clientId;
	std::string clientSecret;
	std::string gptServerUrl;
};

int main() {
	// �滻Ϊ���Baidu API�ͻ���ID����Կ
	std::string clientId = "WssOTBZYUyTKAq0ulFQuyCgO";
	std::string clientSecret = "1oXdY1WiDiZxybLo8RZlUiPDdeF05aGe";

	GptBaiduApiClient gptBaiduClient(clientId, clientSecret);

    // ��ȡ�û��������Ȼ�����ı�
    std::cout << "Enter your message: ";
    std::string userMessage;
    std::getline(std::cin, userMessage);

    // ���� GPT ģ�ͣ������û��������Ϣ
	std::string gptResponse = gptBaiduClient.getinGPT(userMessage);
    std::cout << "GPT Response: \n" << gptResponse << endl;

	return 0;
}
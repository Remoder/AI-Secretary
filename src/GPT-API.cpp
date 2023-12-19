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

	// 获取Baidu Access Token
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

        // 发送 HTTP 请求
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
	// 替换为你的Baidu API客户端ID和密钥
	std::string clientId = "WssOTBZYUyTKAq0ulFQuyCgO";
	std::string clientSecret = "1oXdY1WiDiZxybLo8RZlUiPDdeF05aGe";

	GptBaiduApiClient gptBaiduClient(clientId, clientSecret);

    // 获取用户输入的自然语言文本
    std::cout << "Enter your message: ";
    std::string userMessage;
    std::getline(std::cin, userMessage);

    // 调用 GPT 模型，传递用户输入的信息
	std::string gptResponse = gptBaiduClient.getinGPT(userMessage);
    std::cout << "GPT Response: \n" << gptResponse << endl;

	return 0;
}
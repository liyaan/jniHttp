#ifndef WEB_ASYNC_TASK_HHHHHH_
#define WEB_ASYNC_TASK_HHHHHH_
#include <android/log.h>
#define LOG_TAG ("fromNDK")
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO   , LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__))
#include <string>
#include "curl.h"


typedef struct _web_buffer_t {
    char* buf;
    //buffer orignal size
    int   size;
    //length of data that wrote to buffer
    int   datalen;
} web_buffer_t;

typedef void (*on_web_done_t)(int, const std::string&, void*);

class WebTask
{
 public:

	

	bool SetUrl(const char* url);

	void SetCallback(on_web_done_t cb, void* para = NULL);

	void AddPostString(const char* item_name,  const char* item_data);
	
	void AddPostPicture(const char* item_name, const char* file_path, const char* file_name = NULL);

	// must call DoGetString() or DoGetFile() before start task
	int  DoGetString();

	// must call DoGetString() or DoGetFile() before start task
	// range like "0-255"
	int  DoGetFile(const char* range=NULL);
	
	int  WaitTaskDone();
	int WaitCookieTaskDone();
	const char*  GetResultString();
	const char*  GetFilePath();

    /**
     * @timeo seconds
     */
    void SetConnectTimeout(int timeo);

	
	CURL  *m_curl;
	//CURLM *m_curl_m; 

	int    m_is_getfile;
	curl_slist* headers = NULL;
	// if call DoGetString or DoGetFile
	bool   m_do_func_called;
    bool addHeader(std::string headerString);
    bool addHeaderFrom(std::string headerString);
    bool addCookie(std::string app_cookie);
    void postJsonRequest(std::string strJson);
    void addPostData(std::string requestJson);
	//for post
	struct curl_httppost *m_formpost;
    struct curl_httppost *m_lastptr;
    struct curl_slist *m_headerlist;

	on_web_done_t m_cb;
	void* m_cb_para;

	//for download file
	FILE* m_file;
	std::string m_filepath;

	int   m_web_result;

	//for tracer
	std::string m_url;

    WebTask(const WebTask&);

    ~WebTask();

	WebTask();

private:
	void _init();
	void _add_post_file(const char* item_name, const char* file_path, const char* file_name,  const char* content_type);

	int _on_work_done(int result);

	web_buffer_t m_web_buf;

 private:

	WebTask& operator=(const WebTask&);
};
#endif


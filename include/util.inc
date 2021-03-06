<?php
function parse_properties($txtProperties) {
	$result = array();
	$lines = split("\n", $txtProperties);
	$key = "";
	$isWaitingOtherLine = false;
	foreach ($lines as $i => $line) {
		if (empty($line) || (!$isWaitingOtherLine && strpos($line, "#") === 0))
			continue;
			
		if (!$isWaitingOtherLine) {
			$key = substr($line, 0, strpos($line, '='));
			$value = substr($line, strpos($line, '=')+1, strlen($line));
		}
		else {
			$value .= $line;
		}

		/* Check if ends with single '\' */
		if (strrpos($value, "\\") === strlen($value)-strlen("\\")) {
			$value = substr($value,0,strlen($value)-1)."\n";
			$isWaitingOtherLine = true;
		}
		else {
			$isWaitingOtherLine = false;
		}

		$result[$key] = $value;
		unset($lines[$i]);
	}

	return $result;
}

function make_random_key( $length = 8 ) {
	// 密码字符集，可任意添加你需要的字符
	$chars = 'abcdefghijklmnopqrstuvwxyz0123456789';

	$key = '';
	for ( $i = 0; $i < $length; $i++ )
	{
		// 这里提供两种字符获取方式
		// 第一种是使用 substr 截取$chars中的任意一位字符；
		// 第二种是取字符数组 $chars 的任意元素
		// $password .= substr($chars, mt_rand(0, strlen($chars) - 1), 1);
		$key .= $chars[ mt_rand(0, strlen($chars) - 1) ];
	}

	return $key;
}

function make_random_vcode($length = 4) {
	$chars = '0123456789';
	$key = '';
	for ( $i = 0; $i < $length; $i++ )
	{
		$key .= $chars[ mt_rand(0, strlen($chars) - 1) ];
	}
	
	return $key;	
}

function http_post($url, $data, $debug = false) {
	$cookie_file_path = TMP. '/cookiee.txt';
	$curl = curl_init();
	curl_setopt($curl, CURLOPT_POST, 1 );
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($curl,CURLOPT_USERAGENT, "Mozilla/4.0");
	curl_setopt($curl, CURLOPT_COOKIEJAR,  $cookie_file_path);
	curl_setopt($curl, CURLOPT_COOKIEFILE, $cookie_file_path);
	curl_setopt($curl, CURLOPT_URL, $url);
	curl_setopt($curl, CURLOPT_POSTFIELDS, $data);

	$response = curl_exec($curl);
	$result = json_decode($response, true);
	$error = curl_error($curl);
	if($debug) {
		// 		debug($full_url);
		// 		debug($data);
		// 		debug($response);
		// 		debug($error);
	}


	if($error) {
		$result = array( 'code' => -1, 'message' => $error);
	}

	//$log = "http_post: url=$url \n request data=".print_r($data, true)." \n response=$response \n result=".print_r($result, true)." \n";
	return $result;
}

function validate_email($email) {
	$chars = "/^([a-z0-9+_]|\\-|\\.)+@(([a-z0-9_]|\\-)+\\.)+[a-z]{2,5}\$/i";
	if (strpos($email, '@') !== false && strpos($email, '.') !== false)
	{
		if (preg_match($chars, $email))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

function validate_nickname($nickname) {
	if (strlen($nickname) < 4 || strlen($nickname) > 10) {
		return false;
	}
	return true;
}

function validate_password($password) {
	if (strlen($password) < 6 || strlen($password) > 10) {
		return false;
	}
	
	return true;
// 	$_march = '/^[a-z|0-9]{3,20}/';
// 	if(!preg_match($_march, $_uname)) {
// 		$this->error('用户名非法，请重新输入正确的用户名');
// 		exit;
// 	}
}

function get_client_ip() {
	if(getenv('HTTP_CLIENT_IP')) {
		$onlineip = getenv('HTTP_CLIENT_IP');
	} elseif(getenv('HTTP_X_FORWARDED_FOR')) {
		$onlineip = getenv('HTTP_X_FORWARDED_FOR');
	} elseif(getenv('REMOTE_ADDR')) {
		$onlineip = getenv('REMOTE_ADDR');
	} else {
		$onlineip = $HTTP_SERVER_VARS['REMOTE_ADDR'];
	}
	return $onlineip;
}

import hashlib
import random
import string
import requests
import time

class CodeforcesAPI:
    BASE_URL = 'https://codeforces.com/api/'

    def __init__(self):
        self.last_request_time = 0

    def _make_request(self, method, params=None):
        if params is None:
            params = {}
        url = self.BASE_URL + method
        response = requests.get(url, params=params)
        data = response.json()

        if data['status'] == 'OK':
            return data['result']
        else:
            raise Exception(f"API Error: {data.get('comment', 'No comment provided')}")

    def get_user_info(self, handle):
        method = 'user.info'
        params = {'handles': handle}
        return self._make_request(method, params)

class CodeforcesAPI:
    BASE_URL = 'https://codeforces.com/api/'

    def __init__(self, api_key=None, api_secret=None):
        self.api_key = api_key
        self.api_secret = api_secret
        self.last_request_time = 0

    def _generate_api_sig(self, method, params):
        # Generate a random 6-character string
        rand = ''.join(random.choices(string.digits + string.ascii_letters, k=6))
        
        # Sort parameters lexicographically by key, then by value
        sorted_params = sorted(params.items())
        param_str = '&'.join(f"{k}={v}" for k, v in sorted_params)
        
        # Construct the string to hash
        to_hash = f"{rand}/{method}?{param_str}#{self.api_secret}"
        
        # Compute SHA-512 hash
        hash_obj = hashlib.sha512(to_hash.encode('utf-8'))
        hash_hex = hash_obj.hexdigest()
        
        # Combine rand and hash
        api_sig = rand + hash_hex
        return api_sig

    def _make_request(self, method, params=None, auth=False):
        if params is None:
            params = {}
        
        if auth:
            if not self.api_key or not self.api_secret:
                raise ValueError("API key and secret must be provided for authenticated requests.")
            
            # Add apiKey and time
            current_time = int(time.time())
            params['apiKey'] = self.api_key
            params['time'] = current_time
            
            # Generate apiSig
            api_sig = self._generate_api_sig(method, params)
            params['apiSig'] = api_sig

        # Rate limiting: 1 request per 2 seconds
        elapsed = time.time() - self.last_request_time
        if elapsed < 2:
            time.sleep(2 - elapsed)
        
        url = self.BASE_URL + method
        response = requests.get(url, params=params)
        data = response.json()
        self.last_request_time = time.time()

        if data['status'] == 'OK':
            return data['result']
        else:
            raise Exception(f"API Error: {data.get('comment', 'No comment provided')}")

    def get_user_info(self, handle, auth=False):
        method = 'user.info'
        params = {'handles': handle}
        return self._make_request(method, params, auth)
    
    # Additional methods can be added similarly

if __name__ == "__main__":
    # Replace with your actual API key and secret
    API_KEY = '297eddd7d1088e0b2f8007089606ff02a30a2f66'
    API_SECRET = 'b8bbd1c14da6e1c5c24868c1a58ba0eeac56c40b'
    
    cf_api = CodeforcesAPI(api_key=API_KEY, api_secret=API_SECRET)
    try:
        user_info = cf_api.get_user_info('FranJ', auth=True)
        print(user_info)
        rating = user_info[0]['maxRating']
        print(f"사용자의 Rating: {rating}")
    except Exception as e:
        print(e)
        

class Solution:
    def isPalindrome2(self, s: str) -> bool:
        """
        使用语言特性进行求解
        """
        s = ''.join(i for i in s if i.isalnum()).lower()
        return s == s[::-1]


s = Solution()
print("hello world")

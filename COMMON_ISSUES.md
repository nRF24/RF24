# Here are the most common issues and their solutions.

### I'm not receiving acks!
If you're not receiving acks correctly/reliably on data rates lower than 2MBPS,
try adding a big capacitor close to the module/chip. Example issues: [#264](https://github.com/nRF24/RF24/issues/264) [#211](https://github.com/nRF24/RF24/issues/211).

For this application, please use Electrolytic or Tantalum capacitors. Ceramic capacitors will probably not be good enough.


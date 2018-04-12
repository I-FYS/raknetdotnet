<?php

$files = scandir(__DIR__);

foreach ($files as $file) {
	if (preg_match('/.+\.cpp/', $file)) {
		$data = file_get_contents($file);
		file_put_contents($file, "#pragma unmanaged\n" . $data);
	}
}

?>
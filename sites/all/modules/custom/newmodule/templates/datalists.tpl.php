<?php
?>
	<div class="data-wrapper">
	 <?php
	 foreach($data['items'] as $key => $val) { ?>
	 <div class="tit">
	<?php echo $val['title'] ?> <a style="margin-left:138px;" href='#'>delete</a></div>
	 <div class="img">
	 <img src="<?php print file_create_url($val['url']); ?>">
	 
	 <br/>
	 </div>
		<?php
	  }